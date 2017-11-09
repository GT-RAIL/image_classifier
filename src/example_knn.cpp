#include <example_knn.h>

using namespace std;

ExampleKNN::ExampleKNN()
{
  knn = cv::ml::KNearest::create();
}

void ExampleKNN::trainAndClassify()
{
  // Prepare the training data
  vector< vector<int> > train_lines;
  readCSV("imgs/train.txt", train_lines);
  // Note: our feature vector is 33x25, so number of columns must be 33*25
  cv::Mat train_data(train_lines.size(), 33*25, CV_32FC1);
  cv::Mat train_labels(train_lines.size(), 1, CV_32FC1);
  readImages(train_lines, train_data, train_labels);

  // Train the KNN classifier
  cv::Ptr<cv::ml::TrainData> training_data;
  training_data = cv::ml::TrainData::create(train_data, cv::ml::ROW_SAMPLE, train_labels);
  knn->setIsClassifier(true);
  knn->setAlgorithmType(cv::ml::KNearest::BRUTE_FORCE);
  knn->setDefaultK(1);
  knn->train(training_data);

  // Prepare the test data
  vector< vector<int> > test_lines;
  readCSV("imgs/test.txt", test_lines);
  cv::Mat test_data(test_lines.size(), 33*25, CV_32FC1);
  cv::Mat test_labels(test_lines.size(), 1, CV_32FC1);
  readImages(test_lines, test_data, test_labels);

  // Perform classification
  cv::Mat results(test_data.rows, 1, CV_32FC1);
  knn->findNearest(test_data, 1, results);

  // Report results
  int correct = 0;
  int confusion_matrix[6][6] = {0};
  for (size_t i = 0; i < results.rows; i ++)
  {
    float predicted = results.at<float>(i,0);
    float label = test_labels.at<float>(i, 0);
    if (predicted == label)
    {
      cout << test_lines[i][0] << " Correct, " << predicted << endl;
      correct ++;
    }
    else
    {
      cout << test_lines[i][0] << " Wrong, " << label << " classified as " << predicted << endl;
    }
    confusion_matrix[int(label)][int(predicted)] += 1;
  }

  cout << "\n\nTotal accuracy: " << (float)correct/test_lines.size() << endl;
  cout << "[";
  for (size_t i = 0; i < 6; i ++)
  {
    if (i > 0)
      cout << " ";
    for (size_t j = 0; j < 6; j ++)
    {
      cout << confusion_matrix[i][j];
      if (j < 5)
        cout << ", ";
    }
    if (i < 5)
      cout << "\n";
  }
  cout << "]" << endl;
}

void ExampleKNN::readCSV(string filename, vector< vector<int> > &file_contents)
{
  ifstream file;
  string line;

  file.open(filename.c_str(), ios::in);
  while (!file.eof())
  {
    getline(file, line);
    if (line.empty())
      break;
    size_t split = line.find(',');
    vector<int> line_contents;
    line_contents.push_back(atoi(line.substr(0, split).c_str()));
    line_contents.push_back(atoi(line.substr(split + 1).c_str()));
    file_contents.push_back(line_contents);
  }
  file.close();
}

void ExampleKNN::readImages(vector< vector<int> > &file_contents, cv::Mat &features, cv::Mat &labels)
{
  // Get image data
  vector< vector<float> > train_data_vector;
  for (size_t i = 0; i < file_contents.size(); i ++)
  {
    // Read all images listed in the file in GRAYSCALE, and resize them to 33x25 pixels
    stringstream ss("");
    ss << "imgs/" << file_contents[i][0] << ".png";
    cv::Mat src_image = cv::imread(ss.str(), cv::IMREAD_GRAYSCALE);
    cv::Mat dst_image(33, 25, src_image.type());
    cv::resize(src_image, dst_image, cv::Size(33, 25));

    // Convert image values to a feature vector
    vector<float> feature_vector;
    feature_vector.assign((uchar*)dst_image.datastart, (uchar*)dst_image.dataend);
    train_data_vector.push_back(feature_vector);
  }

  // Convert training data to a cv::Mat object
  cv::Mat data(train_data_vector.size(), train_data_vector[0].size(), CV_32FC1);
  for (size_t i = 0; i < data.rows; i ++)
  {
    for (size_t j = 0; j < data.cols; j ++)
    {
      data.at<float>(i, j) = train_data_vector.at(i).at(j);
    }
  }

  // Convert labels to cv::Mat object
  cv::Mat label(file_contents.size(), 1, CV_32FC1);
  for (size_t i = 0; i < file_contents.size(); i ++)
  {
    label.at<float>(i, 0) = file_contents[i][1];
  }

  data.copyTo(features);
  label.copyTo(labels);
}

int main(int argc, char** argv)
{
  ExampleKNN example;
  example.trainAndClassify();

  return EXIT_SUCCESS;
}