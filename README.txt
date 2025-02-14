=======================================================================================================================
Evagents
Authors & Contributors: Julian Hershey, Andrej Karpathy, Casey Link, David Coleman
Supporters: Eric Hvinden, Max Brage
License: BSD (see end of file)

Project website and attached forum: 
https://sites.google.com/view/evagentsproject/home

=======================================================================================================================

WHAT IS EVAGENTS?
Evagents is a "natural" selection simulator written for Windows platforms. The program contains a world wherein simple 
agents can interact with that world and each other, reproduce, die, run around, eat, breed, communicate, and other 
things, using neural nets to calculate their responses to stimuli. Each agent has a huge number of features available 
to them that they can use in various ways to try and survive long enough to reproduce, extending their solution 
through time. Any time a baby is born its traits are copied from it's parent(s), but with chances of mutations. Thus 
a form of natural selection is applied to create populations of species that can best survive in the world. 
Competition and cooperation are important secondary characteristics that agents must develop, using their brains, a 
neural network with features of Connection-Positive, Dampened, Recurrent, Additive, Weighted, Sigmoid-processed 
outputs that take sensory inputs (in range 0-1), process them with finite but potentially complex iterations, and 
produces outputs (also 0-1) over time and in an initially random structure. As time passes, however, the brains can 
mutate into more efficient forms, via adding/removing connections, changing connection targets and sources, changing 
weights, biases, and dampening factors, and more.

=======================================================================================================================

BUILDING: (for users that want to edit the source code)

To compile Evagents you will need:
+ Microsoft Windows
+ MS SDK for Windows Server 2008 and .NET Framework 3.5 (https://www.microsoft.com/en-us/download/details.aspx?id=11310)
+ OpenGL (http://www.opengl.org/resources/libraries/glut/). Note: OpenGL is typically included in Windows distributions, 
so a manual DL is not usually required.

It will use OpenMP to speed up everything, in case you have multi-core CPU, and OpenGL + GLUI to draw a user interface.

Take the provided .vcproj file and edit the files as you desire, compile and enjoy!

=======================================================================================================================

QUESTIONS, COMMENTS, ISSUES are best posted on Evagents sub-Reddit, available here:
- https://www.reddit.com/r/Evagents/

More details can be learned from our Wiki, located here:
- https://sites.google.com/view/evagentsproject/wiki

=======================================================================================================================

LICENSE CLAUSE:
Redistribution and use in source and binary forms are permitted provided that the above Authors list, project name, 
and this paragraph are duplicated with all distributions, and that any documentation, advertising materials, and other 
materials related to such distribution and use acknowledge that the software was developed by the Authors. The names 
of the Authors may not be used to endorse or promote products derived from this software without specific prior 
written permission. THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, 
WITHOUT LIMITATION, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

=======================================================================================================================
