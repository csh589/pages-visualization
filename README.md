Report for the visualization test
=================================
The projects in this test are compiled by visual studio 2012, with VTK system(Version 6.3.0), and all the projects are built by CMake, which needs an additional config file CMakeLists.txt. <br><br>
This report can be devided into three parts:
* [overall visualization](https://github.com/csh589/pages-visualization/tree/master/OverallVisualization)
* [identify the number of pages](https://github.com/csh589/pages-visualization/tree/master/Mission1-PagesQuantity)
* [extract the word in pages](https://github.com/csh589/pages-visualization/tree/master/Mission2-ExtractWords)
<br>


The first part is about overall visualization. This part creates a window to display the whole configuration of the volume data, and the inner configuration can also be seen directly because of the opacity setting.<br><br>
The second part offers a way to get the number of the pages which the volume data includes. One of the images in the raw data is used in this procedure. After the operation of edge detection and removing noise, a method that detect gradient of gray level is used to evaluate the number of pages.<br><br>
The final part tries to use isosurface method and slice function to display the characters in the data. With Gassian smooth filter, the two methods contribute to clear pictures of the pages in which characters exist.
