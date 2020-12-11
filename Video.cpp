#include "Video.hpp"

Mat frame;
Mat frame3;
Mat actual;
Mat anterior;
Mat resta;
Mat copia;
Mat negro;
Mat frame2;
Mat laplacioan2;
Mat actualC;
Mat anteriorC;
Mat restaC;

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 39;
int sizeG = 3;
int sizeM = 3;
int boderBoxParam = 30;
int lowThresholdCanny = 0;
int max_lowThreshold = 100;
int ratio = 3;
int kernelSize = 3;
int paramSobel = 30;
int paramSobel2 = 100;
int laplace = 0;

void erosion(int, void *) {}

void dilation(int, void *) {}

void gauss(int, void *) {}

void mediana(int, void *) {}

void boderBox(int, void *) {}

void cannyThreshold(int, void *) {}

void laplaciano(int, void *) {}

int Video::leerVideo()
{
    //"ejemploGirl.webm"
    //"raton.mp4"
    //"ejemplo.webm"
    //"casero.mp4"
    VideoCapture video = VideoCapture("raton.mp4");

    if (video.isOpened())
    {
        namedWindow("Video Original", WINDOW_AUTOSIZE);
        namedWindow("Filtros", WINDOW_AUTOSIZE);
        namedWindow("Bordes", WINDOW_AUTOSIZE);
        namedWindow("Operaciones Morfologicos", WINDOW_AUTOSIZE);

        namedWindow("Movimiento", WINDOW_AUTOSIZE);

        createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Video Original",
                       &erosion_elem, max_elem,
                       erosion);
        createTrackbar("Kernel size:\n 2n +1", "Video Original",
                       &erosion_size, max_kernel_size,
                       erosion);
        createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Video Original",
                       &dilation_elem, max_elem,
                       dilation);
        createTrackbar("Kernel size:\n 2n +1", "Video Original",
                       &dilation_size, max_kernel_size,
                       dilation);

        createTrackbar("Mediana", "Video Original", &sizeM, 33, mediana);
        createTrackbar("Gauss", "Video Original", &sizeG, 33, gauss);
        createTrackbar("Border", "Video Original", &boderBoxParam, 255, boderBox);
        createTrackbar("Canny", "Video Original", &lowThresholdCanny, max_lowThreshold, cannyThreshold);
        createTrackbar("Laplaciano", "Video Original", &laplace, 1, laplaciano);

        while (3 == 3)
        {
            video >> frame;
            resize(frame, frame, Size(), 0.5, 0.5);
            copia = frame.clone();

            if (frame.rows == 0 || frame.cols == 0)
                break;

            cvtColor(frame, frame, COLOR_BGR2GRAY);

            if (sizeG % 2 == 0 && sizeG != 0)
            {
                sizeG += 1;
            }

            if (sizeM % 2 == 0 && sizeM != 0)
            {
                sizeM += 1;
            }

            boderBoxParam = (boderBoxParam > 0) ? boderBoxParam : 1;
            if (sizeM > 0)
                medianBlur(frame, frame, sizeM);
            if (sizeG > 0)
                GaussianBlur(frame, frame, Size(sizeG, sizeG), 0);

            boxFilter(frame, frame, -1, Size(boderBoxParam, boderBoxParam));
            Canny(frame, frame2, lowThresholdCanny, lowThresholdCanny * ratio, kernelSize);
            activarLaplace();

            actual = frame2.clone();

            if (anterior.rows == 0 || anterior.cols == 0)
            {
                anterior = frame2.clone();
            }
            resta = cv::abs(actual - anterior);

            anterior = actual.clone();

            aplicarErosion();
            aplicarDilatacion();

            Mat bet = Mat(Size(frame.cols, frame.rows), CV_8UC3, Scalar(0, 0, 0));

            bitwise_and(copia, copia, bet, resta);

            imshow("Video Original", copia);
            imshow("Filtros", frame);
            imshow("Bordes", frame2);
            imshow("Operaciones Morfologicos", resta);
            imshow("Movimiento", bet);

            if (waitKey(22) == 27)
                break;
        }

        destroyAllWindows();
    }
}

void Video::restarImagenes()
{
}

void Video::activarLaplace()
{
    if (laplace != 0)
    {
        Laplacian(frame, laplacioan2, CV_16S, 3, 1, 0);
        convertScaleAbs(laplacioan2, frame2);
    }
}

void Video::aplicarErosion()
{
    int erosion_type = 0;
    if (erosion_elem == 0)
    {
        erosion_type = MORPH_RECT;
    }
    else if (erosion_elem == 1)
    {
        erosion_type = MORPH_CROSS;
    }
    else if (erosion_elem == 2)
    {
        erosion_type = MORPH_ELLIPSE;
    }
    Mat element = getStructuringElement(erosion_type,
                                        Size(2 * erosion_size + 1, 2 * erosion_size + 1),
                                        Point(erosion_size, erosion_size));
    erode(resta, resta, element);
}

void Video::aplicarDilatacion()
{
    int dilation_type = 0;
    if (dilation_elem == 0)
    {
        dilation_type = MORPH_RECT;
    }
    else if (dilation_elem == 1)
    {
        dilation_type = MORPH_CROSS;
    }
    else if (dilation_elem == 2)
    {
        dilation_type = MORPH_ELLIPSE;
    }
    Mat elementD = getStructuringElement(dilation_type,
                                         Size(2 * dilation_size + 1, 2 * dilation_size + 1),
                                         Point(dilation_size, dilation_size));

    dilate(resta, resta, elementD);
}
