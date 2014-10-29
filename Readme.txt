README

CSC 433/533 - Computer Graphics
Program 2 - Fractal Generator

Authors:
Ian Carlson, Christopher Smith

Program Description:
A fractal generator that uses an initiator-generator method to generate
user-defined fractals. The program has three windows, labeled initiator,
generator, and fractal display.

Instructions:

    Initiator:
The initiator starts off in a state that will generate the Koch Snowflake. There is no
requirement that the endpoints of the initiator be connected, so to close a shape,
the start and endpoints must be arranged such that they overlap. In the preset
pattern, the start and endpoints overlap at the top vertex.

All points can be dragged by clicking and dragging with the mouse. The window can be
reset to the default pattern by clicking reset. Clicking the up and down arrows allows
the user to add or remove points to create more or less complex patterns. This does
reset the pattern to a line of evenly spaced points.

    Generator:
This generator starts off in a state that will generate the Koch Snowflake. The two
endpoints are locked and cannot be dragged to reinforce the idea that the generator
will always been rotated and scaled to match the line segment it is being applied to.
The up/down arrows and reset work just like in the initiator.

    Display Fractal:
In Display Fractal, the user can select how many iterations are preformed of the
generator on the initiator using the up and down arrows.

The user can choose to display all iterations, or just the highest iteration selected
using the Show All toggle button.

The generator and initiator are only reloaded when the user presses Go.

Features
 - Generates Fractals
 - Windows can be resized and maintain their aspect ratio
 - Windows are interactive
 - Vertice/Iteration displayed in menu
 - Multiple different fractals can be generated in one run
 - Toggleable option to show all iterations up to the selected one
 -  Colored display when showing multiple iterations
 - Mid 90's Themed Menus

Outstanding Bugs
 - None known

Other Notes:
User beware when using initiator and generator patterns with large numbers of vertices.
The opp lab computers can handle the program running maxed out with the current limits,
but a 32 bit system will definitely run out of ram. We wanted to make our storage
more efficient (i.e. use something other than vectors) to allow for more iterations
before using up all of the ram, but we never got around to it.

We recommend Ctrl-Alt-F2 to switch from the GUI to a shell to kill the program with
top if you overload your Fedora system. Our current record is 6g RAM and 15g 
virtual RAM before the system locks up.
