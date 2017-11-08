# image_classifier
Sample image classification node for the Introduction to Robotics Research vision lab.

## Instructions
This package contains a set of ROS nodes that will subscribe to an image topic from the `raspicam_node`, calculate a feature vector for the image, and query a classifier service to classify the image.  Also included is a script that will train new classifier models.  To get the package to work, you will have to take the following steps:

1. **Calculate features from an image.**  The `image_node.py` script has placeholder code where you should fill in a feature vector from the subscribed image.  How you calculate the feature vector is up to you, as long as you can represent it in a list of floats.
1. **Create training data.**  Once your feature representation is established, you will need to calculate feature vectors for your training images and store them in a .csv file.  There is an example data file, `example_data.csv`, in the data directory.  Each training instance goes on a new line, in the form `feature_1, feature_2, ..., feature_n, label`.
1. **Train a classifier.**  The `train_classifier.py` script has everything you need to train and evaluate a classifier.  You just have to initialize the classifier you want, and set the parameters however you choose.  Running the script will read in the training data, train your classifier, provide a report of results, and save the model to the current directory.
1. **Use your classifier.**  The`classifier_node.py` script will load a classifier from the `data/classifier/` directory and set up a ros service that the `image_node` will connect to.  Move your trained classifier into this directory to use it.  To test image classification, run both the `image_node.py` and `classifier_node.py` scripts, with the `raspicam_node` running on the robot.
1. **(Optional) Change when classification occurs.**  By default, the `image_node` is set up to classify images as soon as they come in.  You may want to change the structure of this node to perform classification only when you need it.
