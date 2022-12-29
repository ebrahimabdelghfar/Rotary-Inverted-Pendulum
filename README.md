# Introduction
This project involves the design and implementation of a rotary inverted pendulum system using Arduino and Simulink. The system consists of a motor with a built-in encoder and an incremental rotary encoder for measuring the angle of the pendulum. The controller for stabilizing the system is implemented using an LQR controller.
# Model

# State Space Model
<p align="center">
  <img src="https://user-images.githubusercontent.com/81301684/209886657-d23bd41b-5b84-484a-a1d1-812a3a5d1917.png" alt="image">
</p>

<p align="center">
  <img src="https://user-images.githubusercontent.com/81301684/209886802-cc0e819c-6bc1-4ef3-a986-052a14be2cd3.png" alt="image">
  <img src="https://user-images.githubusercontent.com/81301684/209886851-dfa734f8-b1f3-44b7-a5bd-99d6ea4dc7a6.png" alt="image2">
</p>

# Video

<p align="center">
  <video src="https://user-images.githubusercontent.com/81301684/209886973-716920ac-b15f-4c18-91d1-c321af55a641.mp4" controls></video>
</p>

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
This project was developed by Ebrahim Abdelghfar with the help of the following papers:

* https://www.researchgate.net/publication/224178913_Modeling_and_control_of_a_rotary_inverted_pendulum_using_various_methods_comparative_assessment_and_result_analysis
* https://www.st.com/content/dam/AME/2019/Educational%20Curriculums/motor-control/Introduction_to_Integrated_Rotary_Inverted_Pendulum_v2.pdf

