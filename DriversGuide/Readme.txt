DEVELOPING SIMULINK DEVICE DRIVERS BLOCKS:
------------------------------------------

This package contains a guide that explains how to develop device driver blocks 
(blocks that perform target specific functions such as, for example, analog 
or digital input or output, or talking to specific hardware devices, when 
executed on a target platform). 

In this guide, the first method to develop device drivers is based on the S-Function 
Builder block. Following chapters also describe different methods based respectively 
on the Legacy Code tool, the MATLAB function block, and the System Object block.

In general, the MATLAB Function and System Object approaches tend to work better
for developing complex drivers and blocks that have to be redistributed and masked 
(e.g. because the end user needs to change parameters often). On the other hand the 
S-Function Builder and LCT approaches might be better for developers that are 
more familiar with C/C++ than (Embedded) MATLAB or System Objects and need 
to quickly develop simple drivers that don't have a lot of parameters. 

Note however that the System Object approach does not work for versions prior to R2015a.

Finally note that while the Simulink Support package for Arduino is used to build the 
examples, the method applies to any other supported target. In fact, as of June 2015, 
some examples for the raspberry pi board are also given.

Special thanks to Sebastian Schaefer and Murat Belge for their invaluable help on this last 
version, an in particular for the chapters on the Legacy Code Tool System Objects.


Contents:
---------

Readme.txt              This file
license.txt             License File

DriverGuide.pdf         Guide for developing device driver blocks

output_slsp.mdl         Output device driver block example (digital output, aka digital write)
input_slsp.mdl          Input device driver block example (digital input, aka digital read)
output_slsp_masked.mdl  Maksed S-Function Builder output device driver block

encoder_slsp.mdl        Encoder read example
encoder_slsp_mega.mdl	Example model containing three encoder read blocks

renc2cpp.m              Utility function needed when working with external C++ libraries

LCT                     Folder containing various examples of drivers built using an approach 
                        based on the Legacy Code Tool (LCT) (instead of the S-Function builder).
                        Specifically there are drivers for digital and input and output blocks,
                        analog output, and encoder read blocks).

EML                     Folder containing various examples of drivers built using an approach 
                        based on the MATLAB function block (instead of the S-Function builder).
                        Specifically there are drivers for digital and input and output blocks,
                        analog output, and encoder read blocks).

SYS                     Folder containing various examples of drivers built using an approach 
                        based on the System Object block (instead of the S-Function builder).
                        Specifically there are drivers for digital and input and output blocks,
                        analog output, and encoder read blocks).

src                     Folder containing source code files for the LCT, EML and SYS approaches



S-Function Builder fix for MATLAB 2013b:
----------------------------------------

IMPORTANT: For MATLAB 2013b you will need to apply a fix for the S-Function builder:
Go to the following page: http://www.mathworks.com/support/bugreports/1006532
scroll down to the bottom, and follow the instructions therein (it basically 
comes down to saving the zip file, opening winzip as administrator, and 
unzipping the file in the MATLAB folder (e.g. C:\Program Files\MATLAB\2013b).

Also note that another issue in MATLAB 2013b causes high memory usage on the 
Arduino side, and thus prevents the upload of models that have many blocks 
and/or high memory requirements. This might sometimes be a problem for boards
with smaller memory footprint like the Uno or Nano.


Before trying to run a model:
-----------------------------

First, you have to open each S-Function Builder block and click on "build" 
to generate the MEX-files (this requires that you have a compiler installed, 
see http://www.mathworks.com/support/compilers/current_release/). 

Also, to run the models on an Arduino board you should make sure that the 
simulink support package is installed (just type "targetinstaller" on the 
matlab command line). Also go to "Tools -> Run on Target Hardware -> 
Prepare to Run" or "Tools -> Run on Target Hardware -> Options..." to make 
sure that the settings correspond to your version of Arduino board.

If you are writing a driver, especially one that uses external libraries, 
please have a look at the guide first (especially pages 19 and 20), 
and also look at the encoder examples to see how some problems were 
solved in those cases. 

Additional examples (for different motor shields) can be found here:
http://www.mathworks.com/matlabcentral/fileexchange/46133


Versions:
--------
Version 1.2, 13-Dec-2012, Initial version.
Version 1.4, 23-Apr-2013, Troubleshooting section added.
Version 1.6, 23-Oct-2013, Included drivers for AF Motor Shield V2
Version 1.8, 13-Nov-2013, Included Embedded MATLAB examples 
Version 1.9, 30-Apr-2014, Documented Embedded MATLAB examples 
Version 2.0, 30-Oct-2014, Added System Object approach and examples 
Version 2.2, 02-May-2015, Added Legacy Code Tool approach and examples 
Version 2.4, 08-Jun-2015, Guide rewritten to document all approaches


Copyright 2015, The MathWorks, Inc.