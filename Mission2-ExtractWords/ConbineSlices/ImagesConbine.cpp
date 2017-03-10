#include <vtkSmartPointer.h>  
#include <vtkImageData.h>  
#include <vtkTIFFReader.h>  
#include <vtkMatrix4x4.h>  
#include <vtkImageReslice.h>  
#include <vtkLookupTable.h>  
#include <vtkImageMapToColors.h>  
#include <vtkImageActor.h>  
#include <vtkRenderer.h>  
#include <vtkRenderWindow.h>  
#include <vtkRenderWindowInteractor.h>  
#include <vtkInteractorStyleImage.h>  
#include <vtkTIFFWriter.h>
#include<string>
#include <vtkImageReader.h>
#include <vtkImageAppend.h>
int main()
{
	char FileName[60],OutputName[60];
	for (int i=0;i<80;i++)
	{
		vtkSmartPointer<vtkImageAppend>append =
		vtkSmartPointer<vtkImageAppend>::New();
		append->SetAppendAxis(1);
		for( int j=1;j<8;j++)
		{
			sprintf(FileName,"D:/VTK/slice_iso/iso-%02d%02d.tif",j,i);
			vtkSmartPointer<vtkTIFFReader> reader=
			    vtkSmartPointer<vtkTIFFReader>::New();
			reader->SetFileName(FileName);
			append->AddInputConnection(reader->GetOutputPort());
		}
		sprintf(OutputName,"D:/VTK/slice_result/iso-%04d.tif",i);
		vtkSmartPointer<vtkTIFFWriter> writer =
			vtkSmartPointer<vtkTIFFWriter>::New();
		writer->SetFileName(OutputName);
		writer->SetInputConnection( append->GetOutputPort());
		writer->Write();
	};

				
				
}
