#include "Headers/Learning.h"

Learning::Learning(int outputCount)
{
    this->outputCount = outputCount;
    image = new Mat(EN, BOY, CV_8UC1, Scalar(255));
    karakter = new Mat(28, 28, CV_8UC1, Scalar(255));
    expectedValue = new double[outputCount];
}



void Learning::translateImage()
{

    //    for(int imgCount = 0; imgCount < cnt ;imgCount++){
    //        for(int i = 0; i < 28;i++){
    //            for(int j = 0 ; j < 28; j++){
    //                Vec3b & color = karakter->at<Vec3b>(i,j);
    //                if(data->data[i][j]>0){
    //                    color[0] = 0;
    //                    color[1] = 0;
    //                    color[2] = 0;
    //                }
    //            }
    //        }
    //    }
}

void Learning::readData()
{
    int ret;
    if (ret = mnist_load("/home/valkyrie/DigitRecognition/Data/train-images-idx3-ubyte", "/home/valkyrie/DigitRecognition/Data/train-labels-idx1-ubyte", &data, &cnt)) {
        printf("An error occured: %d\n", ret);
    } else {
        printf("image count: %d\n", cnt);
    }
    cout<<"Veri Başarıyla Okundu.."<<endl;

}

void Learning::readTestData()
{
    int ret;
    if (ret = mnist_load("/home/valkyrie/BackPropogation/Data/t10k-images-idx3-ubyte", "/home/valkyrie/BackPropogation/Data/t10k-labels-idx1-ubyte", &testData, &testDataCount)) {
        printf("An error occured: %d\n", ret);
    } else {
        printf("test image count: %d\n", testDataCount);
    }
    cout<<"Test Datası Başarıyla Okundu.."<<endl;

}

void Learning::cleanImage(Mat * image)
{

    for(int i = 0; i < image->rows;i++){
        for(int j = 0 ; j < image->cols; j++){
            Vec3b & color = image->at<Vec3b>(i,j);
            color[0] = 255;
            color[1] = 255;
            color[2] = 255;
        }
    }

}


void Learning::getCharacter()
{
    double getImage[28*28];
    Mat img = imread("/home/valkyrie/BackPropogation/giris.png",0);
    string window_name = "Get Image";
    Mat show = imread("/home/valkyrie/BackPropogation/giris.png",0);
    img.copyTo(show);


    Mat paint_scribble = Mat::zeros(img.size(), CV_8UC1);
    paint_scribble.setTo(BLACK);
    Scalar brush_color = RED;
    int brush_width = 2;
    Brush_bag bag;
    bag.window_name = &window_name;
    bag.img_ptr = &show;
    bag.scribble_ptr = &paint_scribble;
    bag.color_ptr = &brush_color;
    bag.width = &brush_width;

    namedWindow(window_name);
    setMouseCallback(window_name, mouse_brush, &bag);
    char key;
    do {
        //imshow("Paint here", show);
        key = waitKey(0);
        switch(key) {
        case 'p':
            for(int i = 0; i < show.rows;i++){
                for(int j = 0; j < show.cols;j++){
                    Vec3b & color = show.at<Vec3b>(i,j);
                    if(color.val[0]==0){
                        cout<<"1";
                    }
                    else{
                        cout<<"0";
                    }
                }
                cout<<endl;
            }

        case 'r':
            for(int c = 0; c < 3; ++c) {
                brush_color[c] = RED[c];
            }
            break;

        case 'b':
            for(int c = 0; c < 3; ++c) {
                brush_color[c] = BLUE[c];
            }
            break;
        case 's':
            cout<<"Please input brush width: ";
            cin>>brush_width;
            break;
        case 'o':
               resizeImage(&show,0);
            for(int i = 0; i < show.rows;i++){
                for(int j = 0; j < show.cols;j++){
                    Vec3b & color = show.at<Vec3b>(i,j);
                    if(color.val[0]==0){
                        getImage[i*28+j] = 1;
                    }
                    else{
                        getImage[i*28+j] = 0;
                    }
                }

            }

            //            for(int i = 0; i < 28;i++){
            //                for(int j = 0 ; j < 28;j++){
            //                    if(getImage[i*28+j]>0){
            //                        cout<<"1"<<" ";
            //                    }else{
            //                        cout<<"0"<<" ";
            //                    }

            //                }
            //                cout<<endl;
            //            }


            myNeuralNetwork->feedForward((double *)&getImage);

            double enBuyuk=0;
            int tespit = 0;
            for(int i = 0; i < 10;i++){
                if(myNeuralNetwork->getOutput()[i]>enBuyuk){
                    enBuyuk=myNeuralNetwork->getOutput()[i];
                    tespit = i;
                }
            }

            cout<<"Detected Image: "<<tespit<<endl;
            resizeImage(&show,1);

            for(int i = 0; i < show.rows;i++){
                for(int j = 0; j < show.cols;j++){
                    Vec3b & color = show.at<Vec3b>(i,j);
                    color[0] = 255;
                }
            }
            break;
        }
    } while(key != 'e');
    imshow("scribble.png", paint_scribble);
    (*image) = paint_scribble.clone();
    show.release();
    img.release();

}

void Learning::showReadCharacter()
{

}

void Learning::resizeImage(Mat * image,int choose){

    /**
     * Resize mat
     */


    //    Mat new_mat;
    //    resize(mat, new_mat, cvSize(kNewWidth, kNewHeight));

    //    /**
    //     * Rescale mat
    //     */
    if(choose == 0){
        resize((*image), (*image), Size(28,28), 1.0, 1.0, INTER_AREA);
        imwrite("/home/valkyrie/BackPropogation/yeniHali.png",*image);

    }
    if(choose == 1){
          resize((*image), (*image), Size(600,600), 1.0, 1.0, INTER_AREA);
    }


    /**
     * Resize IplImage
     */

    //    IplImage* img; // Input
    //    IplImage* new_img = cvCreateImage(cvSize(kNewWidth, kNewHeight), img->depth, img->nChannels);
    //    cvResize(img, new_img);

    /**
     * Rescale IplImage
     */

    //    IplImage* img; // Input
    //    const int new_width = (int) ((float) img->width * kRescaleFactor);
    //    const int new_height = (int) ((float) img->height * kRescaleFactor);
    //    IplImage* new_img = cvCreateImage(cvSize(new_width, new_height), img->depth, img->nChannels);
    //    cvResize(img, new_img);
    //    *image = *image->clone();

}

void Learning::startLearning()
{
    readData();
    const int myNetArray[3] = {784,10,10};
    const int patternSize = (28*28);

    // myNet vektörüne myNetArray atanıyor kısaca.
    vector<int> myNet(myNetArray, myNetArray + sizeof(myNetArray) / sizeof(int));

    double test[patternSize];

    myNeuralNetwork = new Backpropagation(myNet, patternSize);

    double errors[imgCount];
    double currentError = numeric_limits<double>::max();
    unsigned long long int iteration = 0;

    timeval timer;

    gettimeofday(&timer, 0);

    double start = (timer.tv_sec * 1000000) + timer.tv_usec;

    while(currentError > 0.0001)
    {

//        if(iteration > 100) break;
        for(int trainData = 0; trainData < imgCount;trainData++){
            for(int i= 0; i < 28;i++){
                for(int j = 0; j < 28;j++){
                    if(data->data[i][j] > 0){
                        test[i*28+j] = 1;
                    }
                    else{
                        test[i*28+j] = 0;
                    }

                    //cout<<test[i*28+j]<<" ";
                }

            }
        }
        //        cout<<data->label<<endl;
        setExpectedOutputs(data->label);
        //        for(int i = 0; i < outputCount;i++){
        //            cout<<expectedValue[i] <<" ";
        //        }
        //        cout<<endl;
        Pattern Pattern(patternSize, (double *)&test, expectedValue);
        errors[0] = myNeuralNetwork->train(Pattern);

        double largest = errors[0];
        for(int i = 0;i < imgCount;i++){
            if(errors[i] > largest)
            {
                largest = errors[i];
            }
        }
        if(largest < currentError)
        {
            currentError = largest;
        }
        iteration += 1;
        data++;
        if(iteration == cnt-1){
            data=data-cnt-1;
        }
    }

    gettimeofday(&timer, 0);

    double end = (timer.tv_sec * 1000000) + timer.tv_usec;
    // delete myNeuralNetwork;
}


void Learning::setExpectedOutputs(int x)
{
    for(int i = 0; i < outputCount ;i++){
        expectedValue[i] = 0;
    }
    expectedValue[x] = 1;
}

void Learning::testNeuralNetwork()
{
    int dogruSayisi=0;
    readTestData();
    const int patternSize = (28*28);
    double test[28*28];

    cout << "Testing: " << endl;
    cout << "Input | Output" << endl;
    for(int a = 0; a < testDataCount;a++){
        for(int i= 0; i < 28;i++){
            for(int j = 0; j < 28;j++){
                test[i*28+j] = testData->data[i][j];
                //cout<<test[i*28+j]<<" ";

            }
            //cout<<endl;

        }




        myNeuralNetwork->feedForward((double*)&test);

        //        cout<<testData->label<<endl;
        //        for(int i = 0; i < 10;i++){
        //               cout<<"Ciktilar"<<myNeuralNetwork->getOutput()[i] << endl;
        //        }
        double largest=0;
        int founded = 0;
        for(int i = 0; i < 10;i++){
            if(myNeuralNetwork->getOutput()[i]>largest){
                largest = myNeuralNetwork->getOutput()[i];
                founded = i;
            }
        }
        if(testData->label == founded){
            dogruSayisi++;

        }
        //       cout << testData->label << " | " <<founded << endl;

        testData++;
    }
    cout<<"Dogru Sayisi:"<<dogruSayisi<<endl;
    // delete myNeuralNetwork;
}
double *Learning::getExpectedValue() const
{
    return expectedValue;
}

void Learning::setExpectedValue(double *value)
{
    expectedValue = value;
}
