# Autonomous-Garbage-Collector-Rover-using-Image-Processing
# We are presenting a smart robot that could present a viable solution towards efficient waste management which is based on embedded, digital image processing. The system is designed such that it can manually as well as automatically detect and collect the garbage. The detection is done by using the image processing algorithm SSD Mobilenet v2, which has been modified by adding our customized layer to the VGG-16 architecture for better detection. The real time video taken by the USB camera will be processed by the Raspberry Pi. For each frame taken it will detect any garbage present in the frame and categorize the detected garbage as Paper, Plastic, Metal or Glass. Once the sorting and categorization is complete the Raspberry Pi will send signals to the robot. Our robot will calculate its position, calibrate the motors according to the position of the garbage so that it will go to the acquired position and collect the garbage with help of customized robot arm. The pre-categorized collected garbage will be dumped in separate parts of a basket labeled as Paper, Plastic, Metal and Glass.
