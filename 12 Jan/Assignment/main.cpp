#include <iostream>
#include <thread>
#include <vector>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <opencv2/opencv.hpp>

using namespace std;

const int NUM_IMAGES = 100;
const int NUM_THREADS = 4;
queue<cv::Mat> inputQueue;
queue<cv::Mat> outputQueue;
mutex inputMutex;
mutex outputMutex;
condition_variable inputCV;
condition_variable outputCV;
bool isProcessingDone = false;

// Load image from HDD to RAM (Thread 1)
void loadImage(const string &filePath)
{
    for (int i = 1; i <= NUM_IMAGES; ++i)
    {
        cv::Mat image = cv::imread(filePath + "/imgs" + to_string(i) + ".jpg", cv::IMREAD_COLOR);

        {
            unique_lock<mutex> lock(inputMutex);
            inputQueue.push(image);
        }

        inputCV.notify_one();

        cout << "Loaded image: " << filePath + "/imgs" + to_string(i) + ".jpg"
             << " with channels: " << image.channels() << endl;
    }

    isProcessingDone = true;
    inputCV.notify_all();
}

// Process image and convert to grayscale (Threads 2 and 3)
void processImage()
{
    while (true)
    {
        cv::Mat image;

        {
            unique_lock<mutex> lock(inputMutex);
            inputCV.wait(lock, [&]
                         { return !inputQueue.empty() || isProcessingDone; });

            if (inputQueue.empty() && isProcessingDone)
            {
                break;
            }

            image = inputQueue.front();
            inputQueue.pop();
        }

        // Check if the image is not empty and has 3 channels (color image)
        if (!image.empty() && image.channels() == 3)
        {
            cv::Mat grayscaleImage;
            cv::cvtColor(image, grayscaleImage, cv::COLOR_BGR2GRAY);

            {
                unique_lock<mutex> lock(outputMutex);
                outputQueue.push(grayscaleImage);
            }

            outputCV.notify_one(); // Notify waiting threads that output is available
            cout << "Processed image with channels: " << grayscaleImage.channels() << endl;
        }
        else
        {
            // Print a message indicating that the image is skipped
            cout << "Skipped image with unexpected channels or empty image." << endl;
        }
    }
}

// Dump grayscale image from RAM to HDD (Thread 4)
void dumpImage(const string &outputPath)
{
    int imageCount = 1;
    while (true)
    {
        cv::Mat grayscaleImage;

        // Wait for output
        {
            unique_lock<mutex> lock(outputMutex);
            outputCV.wait(lock, [&]
                          { return !outputQueue.empty() || (isProcessingDone && inputQueue.empty()); });

            if (outputQueue.empty() && isProcessingDone && inputQueue.empty())
            {
                break; 
            }

            grayscaleImage = outputQueue.front();
            outputQueue.pop();
        }

        cv::imwrite(outputPath + "/imgs_op" + to_string(imageCount) + "_grayscale.jpg", grayscaleImage);

        cout << "Dumped grayscale image with channels: " << grayscaleImage.channels() << endl;

        ++imageCount;
    }
}

int main()
{
    string inputPath = "/home/pratyushs/Desktop/Sessions/12 Jan/Assignment/imgs";
    string outputPath = "/home/pratyushs/Desktop/Sessions/12 Jan/Assignment/imgs_op";

    // Create threads
    thread loaderThread(loadImage, ref(inputPath));
    vector<thread> processingThreads;
    for (int i = 0; i < NUM_THREADS - 1; ++i)
    {
        processingThreads.emplace_back(processImage);
    }
    thread dumperThread(dumpImage, ref(outputPath));

    // Join threads
    loaderThread.join();
    for (auto &thread : processingThreads)
    {
        thread.join();
    }
    dumperThread.join();

    return 0;
}
