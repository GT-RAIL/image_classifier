#!/usr/bin/env python

# ROS
from image_classifier.srv import Classify
import rospy
from sensor_msgs.msg import CompressedImage


class ImageNode:

    def __init__(self):
        """Initialize image subscriber and classifier client."""
        self.image_subscriber = rospy.Subscriber('/raspicam_node/image/compressed', CompressedImage, self.imageCallback)
        print 'Waiting for classifier service to come up...'
        rospy.wait_for_service('/classifier_node/classify')
        self.classify_client = rospy.ServiceProxy('/classifier_node/classify', Classify)

    def imageCallback(self, image):
        """Process an image and return the class of any sign in the image."""

        ############################################################################################
        # Begin image processing code (You write this!)

        feature_vector = []  # TODO: Fill this in with the features you extracted from the image

        # End image processing code
        ############################################################################################

        classification = self.classify_client(feature_vector)
        print('Classified image as: ' + str(classification.result))


if __name__ == '__main__':
    rospy.init_node('image_node')

    image_node = ImageNode()
    print 'Image node initialized.'

    rospy.spin()
