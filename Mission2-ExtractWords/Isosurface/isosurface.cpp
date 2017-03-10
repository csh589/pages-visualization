    #include <vtkSmartPointer.h>  
    #include <vtkImageData.h>  
    #include <vtkStructuredPoints.h>  
    #include <vtkTIFFReader.h>  
    #include <vtkVolumeRayCastIsosurfaceFunction.h>  
    #include <vtkVolumeRayCastMapper.h>  
    #include <vtkColorTransferFunction.h>  
    #include <vtkPiecewiseFunction.h>  
    #include <vtkRenderer.h>  
    #include <vtkRenderWindow.h>  
    #include <vtkRenderWindowInteractor.h>  
    #include <vtkVolumeProperty.h>  
    #include <vtkAxesActor.h>  
    #include <vtkImageShiftScale.h>  
    #include <vtkImageCast.h>  
    #include <vtkImageGaussianSmooth.h>  
    #include <vtkMatrix4x4.h>
    #include <vtkImageReslice.h>
    #include <vtkTIFFWriter.h> 
    int main(int argc, char *argv[])  
    {  
	//read a series of images.
        vtkSmartPointer<vtkTIFFReader> reader =  
            vtkSmartPointer<vtkTIFFReader>::New(); 
	reader->SetFilePrefix("D:\\slice\\s");
        reader->SetFilePattern("%s%04d.tif");
	reader->SetDataByteOrderToLittleEndian();
	reader->SetDataSpacing(1,1,0.1);
	reader->SetFileNameSliceSpacing(1);
	reader->SetDataExtent(0,1023,0,1023,721,785);
	reader->SetDataScalarTypeToChar();
        reader->Update();  

        //twice Gausian smooth procedure.
	vtkSmartPointer<vtkImageGaussianSmooth>SmoothFilter=
		vtkSmartPointer<vtkImageGaussianSmooth>::New();
	SmoothFilter->SetInputConnection(reader->GetOutputPort());
	SmoothFilter->SetRadiusFactors(5,5,0);
	SmoothFilter->SetStandardDeviation(1.5);
	SmoothFilter->Update();
	reader->Delete();
	vtkSmartPointer<vtkImageGaussianSmooth>SmoothFilter2=
		vtkSmartPointer<vtkImageGaussianSmooth>::New();
	SmoothFilter2->SetInputConnection(SmoothFilter->GetOutputPort());
	SmoothFilter2->SetRadiusFactors(5,5,0);
	SmoothFilter2->SetStandardDeviation(1.5);
	SmoothFilter2->Update();

	//slice and write images.
	//construct the matrix for the data slicing.
	static double axialElements[16] = {  
		1, 0, 0, 0,  
		0, 0, 1, 0,  
		0, -1, 0, 0,  
		0, 0, 0, 1 
		};

	//slice the volume data from the top of the pages to the bottom of them.
	for (int i=0;i<80;i++)
	{
		//setting of the ResliceAxes.
		vtkSmartPointer<vtkMatrix4x4> resliceAxes =  
		vtkSmartPointer<vtkMatrix4x4>::New();  
		resliceAxes->DeepCopy(axialElements);  
		resliceAxes->SetElement(0, 3, 0);  
		resliceAxes->SetElement(1, 3, 40+i*0.1);  
		resliceAxes->SetElement(2, 3, 0);

		//setting of the reslice object.
		vtkSmartPointer<vtkImageReslice> reslice =  
			vtkSmartPointer<vtkImageReslice>::New();  
		reslice->SetInputConnection(SmoothFilter2->GetOutputPort());  
		reslice->SetOutputDimensionality(2);  
		reslice->SetResliceAxes(resliceAxes);  
		reslice->SetInterpolationModeToLinear(); 
		char FileName[50]="";
		sprintf(FileName, "D:\\VTK\\slice_iso7\\iso-%04d.tif", i);

		//writer.
		vtkSmartPointer<vtkTIFFWriter> writer =
			vtkSmartPointer<vtkTIFFWriter>::New();
		writer->SetFileName(FileName);
		writer->SetInputConnection( reslice->GetOutputPort());
		writer->Write();
	}
		
        //extract the isosurface.
        vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction> rayCastFun =  
            vtkSmartPointer<vtkVolumeRayCastIsosurfaceFunction>::New();  
        rayCastFun->SetIsoValue(41350);
      
        //construct the parameter of Raycasting method.
	//volume mapper.
        vtkSmartPointer<vtkVolumeRayCastMapper> volumeMapper =  
            vtkSmartPointer<vtkVolumeRayCastMapper>::New();  
	volumeMapper->SetInputData(SmoothFilter->GetOutput());  
        volumeMapper->SetVolumeRayCastFunction(rayCastFun); 
      
	//construct volume property objet.
        vtkSmartPointer<vtkVolumeProperty> volumeProperty =  
            vtkSmartPointer<vtkVolumeProperty>::New();  
        volumeProperty->SetInterpolationTypeToLinear(); 
        volumeProperty->ShadeOn();  
        volumeProperty->SetAmbient(0.2);
        volumeProperty->SetDiffuse(0.6); 
        volumeProperty->SetSpecular(0.4);
      
	//opacity function.
        vtkSmartPointer<vtkPiecewiseFunction> compositeOpacity =  
            vtkSmartPointer<vtkPiecewiseFunction>::New();  
        compositeOpacity->AddPoint(38000, 0.00);  
        compositeOpacity->AddPoint(42000, 0.40);  
        compositeOpacity->AddPoint(45000, 0.60);  
        volumeProperty->SetScalarOpacity(compositeOpacity);  
        
	//rgb-color function.
        vtkSmartPointer<vtkColorTransferFunction> color =  
            vtkSmartPointer<vtkColorTransferFunction>::New();   
        color->AddRGBPoint(220.0, 0.20, 0.20, 0.20);  
        volumeProperty->SetColor(color);  
      
        // build a volume object and display the object with renderer.     
        vtkSmartPointer<vtkVolume> volume =  
            vtkSmartPointer<vtkVolume>::New();  
        volume->SetMapper(volumeMapper); 
        volume->SetProperty(volumeProperty); 
      
        vtkSmartPointer<vtkRenderer> ren = vtkSmartPointer<vtkRenderer>::New();  
        ren->SetBackground(1.0, 1.0, 1.0);  
        ren->AddVolume(volume);  
      
        vtkSmartPointer<vtkRenderWindow> renWin = vtkSmartPointer<vtkRenderWindow>::New();  
        renWin->AddRenderer(ren);  
        renWin->SetSize(640, 480);  
        renWin->Render();  
        renWin->SetWindowName("IsoSurfaceVolRenderingApp");  
      
        vtkSmartPointer<vtkRenderWindowInteractor> iren =  
            vtkSmartPointer<vtkRenderWindowInteractor>::New();  
        iren->SetRenderWindow(renWin);  
        ren->ResetCamera();  
      
        renWin->Render();  
        iren->Start();  
      
        return EXIT_SUCCESS;  
    }  
