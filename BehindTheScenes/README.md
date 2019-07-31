Requirements
Blender 2.70 or higher
Visual Studio 2017 or higher with the following workloads installed:
.NET desktop development
Universal Windows Platform development
Blender Setup
Open Blender and create a new project.
Add a cube to the scene by pressing Shift + A and selecting "Cube."
In the Properties window, go to the Object tab and set the rotation values for the X, Y, and Z axes to 90 degrees.
In the Timeline window, set the end frame to 60. This will create a 2-second animation at 30 frames per second.
In the Render Properties window, select the output format as PNG and the output path to the desired location.
Render the animation by pressing the Animation button in the Properties window or by using the F12 key.
Export the animation as an image sequence by going to File > Export > Image Sequence.
Visual Studio Setup
Open Visual Studio and create a new Universal Windows Platform project.
Add the image sequence from Blender to the project's Assets folder.
In the MainPage.xaml file, add an Image element and set its Source property to the first image in the image sequence.
In the MainPage.xaml.cs file, add a DispatcherTimer object and set its Interval property to 33 milliseconds (to match the animation's frame rate of 30 frames per second).
In the timer's Tick event, increment a counter and set the Source property of the Image element to the corresponding image in the sequence.
Run the project to see the animation play.
Conclusion
This project demonstrates consist basic animation in Blender and Visual Studio solution.This animations are made for upcoming BehindTheScenes Projects
