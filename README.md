# Autonomous-Garbage-Collector-Rover-using-Image-Processing
 We are presenting a smart robot that could present a viable solution towards efficient waste management which is based on embedded, digital image processing. The system is designed such that it can manually as well as automatically detect and collect the garbage. The detection is done by using the image processing algorithm SSD Mobilenet v2, which has been modified by adding our customized layer to the VGG-16 architecture for better detection. The real time video taken by the USB camera will be processed by the Raspberry Pi. For each frame taken it will detect any garbage present in the frame and categorize the detected garbage as Paper, Plastic, Metal or Glass. Once the sorting and categorization is complete the Raspberry Pi will send signals to the robot. Our robot will calculate its position, calibrate the motors according to the position of the garbage so that it will go to the acquired position and collect the garbage with help of customized robot arm. The pre-categorized collected garbage will be dumped in separate parts of a basket labeled as Paper, Plastic, Metal and Glass.

 **This is my bachelor's thesis. The thesis was completed along with my partner Moin Shahriyar and Sarhan Osman Bhuiya under the supervision of our professor DR. Shazzad Hosain.**
 **Folder Description:**
 - Dataset: We use our own datasets along with kaggle datasets. It can be found under the dataset folder.
 - Garbage Bot Code (Embedded C++): In this folder, all the embedded C++ code we use in our arduino uno can be found which help us to operate our rover.
 - Hardware Measurements: One of the most important part of our garbage rover is the mechanical arms. All the hardware calculations for robotic arm and bot is here in this folder.
   This is a picture of our Garbage bot:
   
   ![ss1](https://github.com/farjana0721/Autonomous-Garbage-Collector-Rover-using-Image-Processing/blob/main/ss1.PNG)

 - Garbage Model: We use machine learning model to train our dataset. Our checkpoints, frozen inference graph files are inside this folder. we use the ssdlite_mobilenet_v2_coco_2018_05_09 to train our datasets. As this model is compatible to our raspberry pi 3.
 - For real time object detection we use a webcam. The code for the webcam to detect object is stored in Object_detection_webcam.py
 - Here is the component list we use for our thesis:
   
   ![ss1](https://github.com/farjana0721/Autonomous-Garbage-Collector-Rover-using-Image-Processing/blob/main/ss2.PNG)
 
