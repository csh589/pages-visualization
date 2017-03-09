  
#include <vtkSmartPointer.h>  
#include <vtkTIFFReader.h>  
#include <vtkImageViewer2.h>  
#include <vtkRenderer.h>  
#include <vtkRenderWindow.h>  
#include <vtkRenderWindowInteractor.h>  
  
int main()  
{  
    vtkSmartPointer<vtkTIFFReader> reader =  
        vtkSmartPointer<vtkTIFFReader>::New();  
    reader->SetFileName("D:\\VTK\\slice_result\\iso-0068.tif");  
    reader->Update();  
  
    vtkSmartPointer<vtkImageViewer2> viewer =  
        vtkSmartPointer<vtkImageViewer2>::New();  
    viewer->SetInputConnection(reader->GetOutputPort());  
  
    //设置基本属性  
    viewer->SetSize(640,480);  
    viewer->SetColorLevel(37000);  
    viewer->SetColorWindow(3500);  
    viewer->SetSlice(40);  
    viewer->SetSliceOrientationToXY();  
    viewer->Render();  
    viewer->GetRenderer()->SetBackground(1,1,1);  
    viewer->GetRenderWindow()->SetWindowName("ImageViewer2D");  
  
    vtkSmartPointer<vtkRenderWindowInteractor> rwi =  
        vtkSmartPointer<vtkRenderWindowInteractor>::New();  
    //设置交互属性  
    viewer->SetupInteractor(rwi);  
  
    rwi->Start();  
  
    return 0;  
}