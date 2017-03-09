 
#include <vtkSmartPointer.h>  
#include <vtkTIFFReader.h>  
#include <vtkImageSobel2D.h>  
#include <vtkImageExtractComponents.h>  
#include <vtkImageMathematics.h>  
#include <vtkImageData.h>  
#include <vtkImageShiftScale.h>  
#include <vtkImageActor.h>  
#include <vtkRenderer.h>  
#include <vtkRenderWindow.h>  
#include <vtkRenderWindowInteractor.h>  
#include <vtkInteractorStyleImage.h>  
#include <vtkImageCast.h>  
#include <vtkImageAnisotropicDiffusion2D.h>  
#include <vtkImageActor.h>  
#include <vtkCamera.h>    
#include <vtkInteractorStyleImage.h>
#include <vtkTIFFWriter.h>  
int main()  
{  
	//read one of the images in the raw data.
    vtkSmartPointer<vtkTIFFReader> reader =  
        vtkSmartPointer<vtkTIFFReader>::New();  
    reader->SetFileName("D:\\slice\\s0001.tif");
    reader->Update();  
	//employ sobel operator twice to the edge detection in the axis of Y(height of the picture).
    vtkSmartPointer<vtkImageSobel2D> sobelFilter =  
        vtkSmartPointer<vtkImageSobel2D>::New();  
    sobelFilter->SetInputConnection(reader->GetOutputPort());  
  
    vtkSmartPointer<vtkImageExtractComponents> ySobel =  
        vtkSmartPointer<vtkImageExtractComponents>::New();  
    ySobel->SetComponents(1);  
    ySobel->SetInputConnection(sobelFilter->GetOutputPort());  
    ySobel->Update();  
  
    vtkSmartPointer<vtkImageMathematics> absYsobel =  
        vtkSmartPointer<vtkImageMathematics>::New();  
    absYsobel->SetOperationToAbsoluteValue();  
    absYsobel->SetInputConnection(ySobel->GetOutputPort());  
    absYsobel->Update();  
  
    double yRange[2];  
    absYsobel->GetOutput()->GetScalarRange(yRange);  
  
	//change the value of pixels in order to display the picture properly.
    vtkSmartPointer<vtkImageShiftScale> yShiftScale =  
        vtkSmartPointer<vtkImageShiftScale>::New();  
    yShiftScale->SetOutputScalarTypeToUnsignedChar();  
    yShiftScale->SetScale(1020 / yRange[1]);  
    yShiftScale->SetInputConnection(absYsobel->GetOutputPort());  
    yShiftScale->Update();  

	//the second sobel filter.
	vtkSmartPointer<vtkImageSobel2D> sobelFilter2 =  
        vtkSmartPointer<vtkImageSobel2D>::New();  
    sobelFilter2->SetInputConnection( yShiftScale->GetOutputPort());

    vtkSmartPointer<vtkImageExtractComponents> yySobel =  
        vtkSmartPointer<vtkImageExtractComponents>::New();  
    yySobel->SetComponents(1);  
    yySobel->SetInputConnection(sobelFilter2->GetOutputPort());  
    yySobel->Update();  
  
    vtkSmartPointer<vtkImageMathematics> absYysobel =  
        vtkSmartPointer<vtkImageMathematics>::New();  
    absYysobel->SetOperationToAbsoluteValue();  
    absYysobel->SetInputConnection(ySobel->GetOutputPort());  
    absYysobel->Update();  
  
    double yyRange[2];  
    absYysobel->GetOutput()->GetScalarRange(yyRange);  
  
    vtkSmartPointer<vtkImageShiftScale> yyShiftScale =  
        vtkSmartPointer<vtkImageShiftScale>::New();  
    yyShiftScale->SetOutputScalarTypeToUnsignedChar();  
    yyShiftScale->SetScale(1020 / yyRange[1]);  
    yyShiftScale->SetInputConnection(absYsobel->GetOutputPort());  
    yyShiftScale->Update();  
	
	//use Anisotropic Diffusion to lower the effection of noise.
	vtkSmartPointer<vtkImageAnisotropicDiffusion2D> diffusion =  
        vtkSmartPointer<vtkImageAnisotropicDiffusion2D>::New();  
    diffusion->SetInputConnection(yyShiftScale->GetOutputPort());  
    diffusion->SetNumberOfIterations(100);  
    diffusion->SetDiffusionThreshold(20);  
    diffusion->Update();  

	//write the image for the next step of pages' check.
	vtkSmartPointer<vtkTIFFWriter> writer=
		vtkSmartPointer<vtkTIFFWriter>::New();
	writer->SetFileName("D:\\vtk\\slice-dealed.tif");
	writer->SetInputConnection(diffusion->GetOutputPort());
	writer->Write();

	//display the generated picture.
    vtkSmartPointer<vtkImageActor> ySobelActor =  
        vtkSmartPointer<vtkImageActor>::New();  
    ySobelActor->SetInputData(diffusion->GetOutput());  
 
    vtkSmartPointer<vtkRenderer> ySobelRender =  
        vtkSmartPointer<vtkRenderer>::New();   
    ySobelRender->AddActor(ySobelActor);  
    ySobelRender->ResetCamera();  
    ySobelRender->SetBackground(1, 1, 1);  

    vtkSmartPointer<vtkRenderWindow> rw =  
        vtkSmartPointer<vtkRenderWindow>::New();  
    rw->AddRenderer(ySobelRender);  
    rw->SetSize(960, 960);  
    rw->SetWindowName("Edge by Soebl");  
  
    vtkSmartPointer<vtkRenderWindowInteractor> rwi =  
        vtkSmartPointer<vtkRenderWindowInteractor>::New();  
    vtkSmartPointer<vtkInteractorStyleImage> style =  
        vtkSmartPointer<vtkInteractorStyleImage>::New();  
    rwi->SetInteractorStyle(style);  
    rwi->SetRenderWindow(rw);  
    rwi->Initialize();  
    rwi->Start();  
  
    return 0;  
}  