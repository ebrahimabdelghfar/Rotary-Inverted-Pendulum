# Software 
Matlab 2020a
# Introduction
This project involves the design and implementation of a rotary inverted pendulum system using Arduino and Simulink. The system consists of a motor with a built-in encoder and an incremental rotary encoder for measuring the angle of the pendulum. The controller for stabilizing the system is implemented using an LQR controller.
# Requirments 
* Arduino uno
* Incremental encoder 
* motor with built-encoder 
* 12V Battery 2200 mah
* H-bridge L298N 2A
* Breadboard
# Steps 
1. Desgin the system  and assemble it
2. Parameter estimaton for the motor to get the the motor coffecient
    1. give the motor a $\pm 12V$  signal
    2. Collect of the $V$ and $\frac{rad}{sec}$ in an excel file 
    3. Import the reading in the Matlab
    4. Build a simulated model using simscape library as the following fig: ![image](https://user-images.githubusercontent.com/81301684/209942131-afcef869-960e-4c80-8c42-cd1c56d04ce5.png)
    5. Using the Parameter-Estimator app of simulink to predict the measurments between simulated and real data
3. Get the gain of LQR by using the mathmatical model built on Matlab 
4. Use the hardware in loop as following :![image](https://user-images.githubusercontent.com/81301684/209944508-2076fb9c-0b63-4146-bc5e-c6d17b49314f.png) <br>
## Note
* When you work with the code and model you must include the repo in Matlab path
* Include the encoder function 
* Enter the motor parameter in workspace 

# State Space Model
<p align="center">
  <img src="https://user-images.githubusercontent.com/81301684/209886657-d23bd41b-5b84-484a-a1d1-812a3a5d1917.png" alt="image">
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/81301684/209886802-cc0e819c-6bc1-4ef3-a986-052a14be2cd3.png" alt="image">
  <img src="https://user-images.githubusercontent.com/81301684/209886851-dfa734f8-b1f3-44b7-a5bd-99d6ea4dc7a6.png" alt="image2">
</p>

# Video


https://user-images.githubusercontent.com/81301684/209939626-c5e16321-2852-4be7-b2b8-c4163fcaf9ac.mp4



# Limitations
There is no swing up functionality in the current model. Additionally, there is some vibration present in the system. The system is able to work within an angle range of +20 to -20 degrees, beyond which it will turn off until the pendulum is returned within this range.

# Usage
To use the system, connect the Arduino board to a computer and open the Simulink model. Run the model and the system will start operating. The angle of the pendulum and the control signal can be monitored in the scope blocks in the model.

# Files

The repository includes the following files:
* MotorParameter.mat "which contain the esimtated motor parameter using parameter estimator tool"
* MotorModelEstimated.slx "A simulink file that contain a simscape model for the motor to be used in parameter estimation"
* model_inverted_rotary_pendulumV4.mlx "A live matlab script at which the model is applied ,in addition to be used in getting the response and stability gains"
* RotaryInvertedPendulumHardwareInLoop.slx "A simulink Hardware in loop code for arduino uno that was programmed using simulink"
* Driver guide "folder that contain the simulink's arduino encoder driver in it" 

# Credits
This project was developed by Ebrahim Abdelghfar and Hesham Hesham with the help of the following papers and videos:

* https://www.researchgate.net/publication/224178913_Modeling_and_control_of_a_rotary_inverted_pendulum_using_various_methods_comparative_assessment_and_result_analysis
* https://www.st.com/content/dam/AME/2019/Educational%20Curriculums/motor-control/Introduction_to_Integrated_Rotary_Inverted_Pendulum_v2.pdf4
* https://www.youtube.com/watch?v=ZGICyE1pDxo

