#include <vtkSmartPointer.h>
#include <vtkTIFFReader.h>
#include <vtkImageData.h>
int CheckPixels(int start,int end,int xlabel,int GradientCount,vtkSmartPointer<vtkTIFFReader> reader);
int main()
{
	vtkSmartPointer<vtkTIFFReader> reader =  
            vtkSmartPointer<vtkTIFFReader>::New();  
    	reader->SetFileName("D:\\vtk\\slice-dealed.tif");
    	reader->Update();  
	int PageCount1=0,PageCount2=0,PageCount3=0,PageCount4=0;
	int SumPages;

	//the range of the pages' xvalue is 115~910.
	for (int xvalue=390;xvalue<600;xvalue++)
	{
		PageCount1=CheckPixels(455,475,xvalue,PageCount1,reader);
		PageCount2=CheckPixels(475,495,xvalue,PageCount2,reader);
		PageCount3=CheckPixels(495,518,xvalue,PageCount3,reader);
		PageCount4=CheckPixels(518,538,xvalue,PageCount4,reader);
	}
	SumPages=PageCount1+PageCount2+PageCount3+PageCount4;
	std::cout<<"the number of pages are: "<<SumPages;
	while(1);
	return 0;
}
int CheckPixels(int start,int end,int xlabel,int GradientCount,vtkSmartPointer<vtkTIFFReader> reader)
{
	int count=0;
	for ( int j=start; j<end; j++)
		{
			unsigned char* pixel=
				(unsigned char*)( reader->GetOutput()->GetScalarPointer(xlabel,j,0));
			unsigned char* pixel1=
				(unsigned char*)( reader->GetOutput()->GetScalarPointer(xlabel,j+1,0));
			if (*pixel1-*pixel>5)
			{
				count+=1;
			}
		}
		if(count>GradientCount)
		{
			GradientCount=count;
		}
		return GradientCount;
};
