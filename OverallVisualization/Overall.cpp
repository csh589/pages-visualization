
#include <vtkActor.h>  
#include <vtkCamera.h>  
#include <vtkProperty.h>  
#include <vtkPolyData.h>  
#include <vtkRenderer.h>  
#include <vtkRenderWindow.h>  
#include <vtkSmartPointer.h>  
#include <vtkPolyDataMapper.h>  
#include <vtkCylinderSource.h>  
#include <vtkRenderWindowInteractor.h>  
#include <vtkTIFFReader.h>
#include <vtkPiecewiseFunction.h>
#include <vtkPolyDataNormals.h>
#include <vtkStripper.h>
#include <vtkVolumeProperty.h>
#include <vtkColorTransferFunction.h>
#include <vtkVolumeRayCastCompositeFunction.h>
#include <vtkVolumeRayCastMapper.h>
#include <vtkMergePoints.h> 
#include <vtkMarchingCubes.h>

int main()
{
	vtkRenderer *aRender = vtkRenderer::New(); 
	vtkRenderWindow *renWin=vtkRenderWindow::New();
	renWin->AddRenderer(aRender); 
	vtkRenderWindowInteractor *iRen=
		vtkRenderWindowInteractor::New();
	iRen->SetRenderWindow(renWin);

	vtkSmartPointer<vtkTIFFReader> Reader = 
		vtkSmartPointer<vtkTIFFReader>::New();
    Reader->SetFilePrefix("D:\\slice\\s"); 
    Reader->SetFilePattern("%s%04d.tif"); 
    Reader->SetDataByteOrderToLittleEndian();
    Reader->SetDataSpacing(1, 1, 0.1); 
    Reader->SetFileNameSliceSpacing(1); 
    Reader->SetDataExtent(0, 1023,0,1023, 0, 200);
	Reader->SetDataScalarTypeToChar();
	Reader->Update();
	std::cout<<"1";

	vtkPiecewiseFunction*opacityTransferFunction=
		vtkPiecewiseFunction::New();
	opacityTransferFunction->AddSegment(40000, 0.0, 41500, 0.5);
	opacityTransferFunction->AddSegment(41500, 0.5, 42000, 0.7);
	opacityTransferFunction->AddSegment(42000, 0.7, 42500, 1.0);


	vtkColorTransferFunction *colorTransferFunction = 
		vtkColorTransferFunction::New();
	colorTransferFunction->AddRGBPoint(3050, 0.5, 0.5, 0.5);
	colorTransferFunction->ClampingOff();


	vtkPiecewiseFunction *gradientTransferFunction = 
		vtkPiecewiseFunction::New();
	gradientTransferFunction->AddPoint(0, 0.0);
	gradientTransferFunction->AddPoint(500, 0.3);
	gradientTransferFunction->AddPoint(1300, 1);


	vtkVolumeProperty*volumeProperty=
		vtkVolumeProperty::New();
	volumeProperty->SetColor(colorTransferFunction);
	volumeProperty->SetScalarOpacity(opacityTransferFunction);
	volumeProperty->SetGradientOpacity(gradientTransferFunction);


	volumeProperty->SetInterpolationTypeToLinear();
	volumeProperty->ShadeOn(); 
	volumeProperty->SetAmbient(0.4);
	volumeProperty->SetDiffuse(0.6);
	volumeProperty->SetSpecular(0.2);




	vtkVolumeRayCastCompositeFunction *compositeRaycastFunction = 
		vtkVolumeRayCastCompositeFunction::New();
	vtkVolumeRayCastMapper *volumeMapper = 
		vtkVolumeRayCastMapper::New();

	volumeMapper->SetVolumeRayCastFunction(compositeRaycastFunction);
	volumeMapper->SetInputData(Reader->GetOutput());

	vtkVolume *volume = vtkVolume::New();
	volume->SetMapper(volumeMapper);
	volume->SetProperty(volumeProperty);

	aRender->AddVolume(volume); 
	aRender->SetBackground(1, 1, 1);

	renWin->SetSize(1000, 1000); 
	renWin->Render(); 

	iRen->Initialize();
	iRen->Start(); 
	return EXIT_SUCCESS;
}