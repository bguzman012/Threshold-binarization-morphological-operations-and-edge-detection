#include <cstring>
#include <iostream>
#include <cstdlib>
#include <opencv2/core/core.hpp>
#include <cmath>
#include <vector>
#include <fstream>
#include <sstream>
#include <dirent.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/videoio/videoio.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <math.h>
#include <cmath>
#include <stdlib.h>
#include <ctime>

using namespace std;
using namespace cv;

class Video
{
public:
    int leerVideo();    
    void restarImagenes();
    void realizarOperacionAnd();
    void aplicarErosion();
    void aplicarDilatacion();
    void activarLaplace();
};
