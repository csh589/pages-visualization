Report for the visualization test
=================================
The projects in this test are compiled by visual studio 2012, with VTK system(Version 6.3.0), and all the projects are built by CMake, which needs an additional config file CMakeLists.txt. <br><br>
This report can be devided into three parts:
* overall visualization
* identify the number of pages
* extract the word in pages<br><br>


The first part is about overall visualization. This part creates a window to display the whole configuration of the volume data, and the inner configuration can also be seen directly by adjust the opacity with the mouse botton.<br><br>
The second part offers a way to get the number of the pages which the volume data shows. One of the images in the data is used in this procedure. After the operation of edge detection and removing noise, a method that detect gradient of gray level is used to elevate the number of pages.<br><br>
The final part try to conbine isosurface method and slice function. The two methods contribute to a clear picture of the pages in which words exist.
