#include <ros/ros.h>
#include <message_filters/subscriber.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/PointCloud2.h>
#include <pcl_ros/point_cloud.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/aruco.hpp>

#define ARUCO 0
#define CHARUCO 1



void mySigintHandler(int sig)
{
   ros::shutdown();
}

int mode = CHARUCO;

bool first = true;
cv::FileStorage fs_;
int id_marker_calib;// = 9;
double size_marker;// = 0.1778;
std::string file_name;// = "/home/sara/data.yml";
std::string camera_topic;// = "/summit_xl/realsense/image_raw";
std::string camera_name;


void writeMat(std::fstream &f, cv::Mat &m, std::string mat_name)
{
    m.convertTo(m,CV_64F);
    f << std::endl << "float data" << mat_name << "[" << m.cols*m.rows <<"] = {";
    for(int i=0;i< m.rows;i++)
    {
        for (int j=0; j<m.cols;j++)
        {
          //  if (m.type() == CV_32F)
          //      f << m.at<float>(i,j);
          //  else if (m.type() == CV_64F)
                 f << m.at<double>(i,j);

            if (!(i == m.rows-1 && j == m.cols-1))
                f << ",";
        }
    }
    f << "};" << std::endl;
    f << "cv::Mat " << mat_name << "(" << m.rows << "," << m.cols << ", CV_32F, data" << mat_name << ");"<< std::endl;
}

void writeFloat(std::fstream &f, float v, std::string v_name)
{
    f << std::endl << "float " << v_name << "=" << v << ";" << std::endl;
}

void callback(const sensor_msgs::Image::ConstPtr &msg_rgb)
{


  /// Recibir imagen
  ROS_INFO("Receiving image...");
  if (first)
  {
    fs_.open(file_name, cv::FileStorage::WRITE);
    if (!fs_.isOpened())
    {
      ROS_ERROR("Error creating file");
      return;
    }
    first = false;
  }

  /// Crear variables
  cv::Mat H(3,3,CV_32F);
  cv::Mat plano(4,1,CV_64F);
  cv::Mat H2;
  float sig;

  bool isTransformKnown = false;


  /// Tratamiento imágenes rgb, de profundidad y pointloud
  std::stringstream topic_d, topic_pc;
  topic_d << camera_topic <<"/depth/image_rect_raw";
  topic_pc << camera_topic <<"/depth_registered/points";

  sensor_msgs::Image::ConstPtr depth = ros::topic::waitForMessage<sensor_msgs::Image>(topic_d.str());
  sensor_msgs::PointCloud2::ConstPtr pc = ros::topic::waitForMessage<sensor_msgs::PointCloud2>(topic_pc.str());

  cv_bridge::CvImagePtr cv_ptr_depth;
  try
  {
    cv_ptr_depth = cv_bridge::toCvCopy(depth, sensor_msgs::image_encodings::TYPE_16UC1);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  cv::Mat img_depth = cv_ptr_depth->image;
  double min, max;
  minMaxLoc(img_depth, &min, &max);
  cv::Mat depth_normalized;
  double alpha = 255.0/(max-min);
  img_depth.convertTo(depth_normalized, CV_8U, alpha, -min*alpha);

  imwrite("/home/irobot/datos/depth.png",depth_normalized);


  // Convert to pcl point cloud
  pcl::PointCloud<pcl::PointXYZRGB>::Ptr cloud_msg (new pcl::PointCloud<pcl::PointXYZRGB>);
  pcl::fromROSMsg(*pc,*cloud_msg);

  std::fstream file_name1;
  file_name1.open("/home/irobot/datos/pointcloud.txt",std::fstream::in | std::fstream::out | std::fstream::trunc);

  for (const auto& point: cloud_msg->points)
     file_name1  << point.x << " " << point.y << " " << point.z << std::endl;
  file_name1.close();

  // Convertir imagen a Mat
  // Convert ROS image to OpenCV image
  cv_bridge::CvImagePtr cv_ptr_rgb;
  try
  {
    cv_ptr_rgb = cv_bridge::toCvCopy(msg_rgb, sensor_msgs::image_encodings::BGR8);
  }
  catch (cv_bridge::Exception& e)
  {
    ROS_ERROR("cv_bridge exception: %s", e.what());
    return;
  }
  cv::Mat img;
  img = cv_ptr_rgb->image;
  resize(img,img,cv::Size(1500,1000));

  cv::Ptr<cv::aruco::Dictionary> dictionary;

  if (mode == ARUCO)
  {
      dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_ARUCO_ORIGINAL);
  }
  else if (mode == CHARUCO)
  {
     // dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_ARUCO_ORIGINAL);

      dictionary = cv::aruco::getPredefinedDictionary(cv::aruco::DICT_4X4_250);
  }

  /// Buscar aruco en la imagen de entrada
  std::vector<int> ids;
  std::vector<std::vector<cv::Point2f> > corners;
  cv::aruco::detectMarkers(img, dictionary, corners, ids);

  cv::aruco::drawDetectedMarkers(img, corners, ids);
  imwrite("/home/irobot/datos/rgb.png",img);

  cv::namedWindow( "ARUCO", CV_WINDOW_NORMAL );
  imshow("ARUCO", img);
  cv::waitKey(1);


  std::vector<cv::Point2f> detectedCorners;
  bool is_marker = false;
  std::cout << corners.size() << std::endl;
  for (int i=0; i<corners.size(); i++)
  {
    if (ids[i] == id_marker_calib)
    {
      detectedCorners = corners[i];
      is_marker = true;
    }
  }

  if (mode == CHARUCO)
  {

      // Escribir esquinas. ¿Que me de él la homografía, o tengo que rehacer todo?
      //////////// Guardar datos para depuración
      std::fstream file_name2;
      file_name2.open("/home/irobot/datos/esquinasArucoImagenRGB_Charuco.txt",std::fstream::in | std::fstream::out | std::fstream::trunc);

      for (int i=0; i<corners.size(); i++)
      {
          for (const auto& point: corners[i])
             file_name2  << point.x << " " << point.y << std::endl;
      }

      file_name2.close();
      return;
  }
  double rel_m_pixls;

  if (!is_marker)
  {
    ROS_INFO("Marker not detected");
  }

  else
  {

    /// Cálculo de la homografía
    // Cálculo del offset inicial: hay que colocar el centro del aruco aproximadamente a 625mm desde donde acaba el soporte de la herramienta(más o menos donde acaba el SICK)
    // y centrado horizontalmente respecto al eje de la cámara.
    // La escala es de 1.25mm/pxl. Como el aruco es de 200mm, el offset entre los puntos es de 160pxls.
    // El aruco aparecería en el centro de la zona reconstruída, siendo la imagen reconstruida de 1500x1000.
    // Las coordenadas para el origen del aruco serían, para la x: (1500-160)/2, y para la y: (1000-160)/2

    std::vector<cv::Point2f> inputQuad;
    float o_x = 670;//detectedCorners[0].x+2000
    float o_y= 420; //detectedCorners[0].y+2000;
    float offset = 160;//abs (detectedCorners[1].x - detectedCorners[0].x);
    inputQuad.push_back(cv::Point2f(o_x, o_y));
    inputQuad.push_back(cv::Point2f(o_x+offset, o_y));
    inputQuad.push_back(cv::Point2f(o_x+offset, o_y+offset));
    inputQuad.push_back(cv::Point2f(o_x, o_y+offset));

    //////////// Guardar datos para depuración
    std::fstream file_name2;
    file_name2.open("/home/irobot/datos/esquinasArucoImagenRGB.txt",std::fstream::in | std::fstream::out | std::fstream::trunc);

    for (const auto& point: detectedCorners)
       file_name2  << point.x << " " << point.y << std::endl;
    file_name2.close();

    std::fstream file_name3;
    file_name3.open("/home/irobot/datos/esquinasArucoImagenHomografia.txt",std::fstream::in | std::fstream::out | std::fstream::trunc);

    for (const auto& point: inputQuad)
       file_name3  << point.x << " " << point.y << std::endl;
    file_name3.close();

    ////////////

    //Búsqueda de homografía
    H = findHomography( detectedCorners, inputQuad, CV_RANSAC );
    std::cout << H << std::endl;

    cv::Mat img_homography;
    warpPerspective(img,img_homography,H,cv::Size(1500,1000)); //Ajustar el tamaño
  //  resize(img_homography, img_homography, Size(1500,1000));

    cv::namedWindow( "ARUCO_H", CV_WINDOW_NORMAL );
    imshow("ARUCO_H", img_homography);

    imwrite("/home/irobot/datos/cenital.jpg", img_homography);

    int ancho_pixls = abs (inputQuad[0].x - inputQuad[2].x); //Dividir entre 4 es porque reescalo la imagen
    int alto_pixls = abs (inputQuad[0].y - inputQuad[2].y);  //Dividir entre 4 es porque reescalo la imagen

    float rel_m_pixls_a = size_marker / ancho_pixls;
    float rel_m_pixls_alto = size_marker / alto_pixls;

    std::cout << rel_m_pixls_a << std::endl;
    std::cout << rel_m_pixls_alto << std::endl;

    rel_m_pixls = rel_m_pixls_a;
    cv::waitKey(0);

    /// Cálculo del plano de la chapa

    //Eliminar los puntos que son nan
    std::vector<int> indices;

    //Corregir homografía para trabajar con imágenes de 640x480
    cv::Mat imgLR;
    resize(img,imgLR,cv::Size(640,480));
    H2 = cv::Mat(3,3,CV_32FC1);
    double dataT[9] = {1500.0/640, 0,   0,
                        0, 1000.0/480, 0,
                        0,     0,    1 };
    cv::Mat T = cv::Mat(3,3,CV_64F, dataT);

    H2=H*T;

    //Partimos de los puntos más cercanos a la cámara en la imagen.
    //En particular, seleccionaremos los dos tercios inferiores de la imagen, con un muestreo de un punto de cada 10 para evitar problemas de memoria al resolver el problema SVD.
    float alto = imgLR.rows;
    float ancho = imgLR.cols;

    std::vector<int> range_y;
    for (int i=round(alto/3); i<alto; i=i+10) range_y.push_back(i);

    //Cogemos todas las columnas
    std::vector<int> range_x;
    for (int i=0; i<ancho; i=i+10) range_x.push_back(i);


    //Seleccionamos los puntos correspondientes de la nube de puntos. Usamos la matriz xyz para poder tener los puntos dispuestos según la imagen.
    //Otra opción es tener en cuenta que las filas del array data están ordenadas siguiendo el orden de las filas de la imagen.
    pcl::PointCloud<pcl::PointXYZRGB>::Ptr puntos_chapa (new pcl::PointCloud<pcl::PointXYZRGB>);
    puntos_chapa->reserve(ancho*alto/2);
    puntos_chapa->width = round(range_x.size());
    puntos_chapa->height = round(range_y.size());


    for (int i=0;i<puntos_chapa->width;i++)
    {
        for (int j=0; j<puntos_chapa->height; j++)
            puntos_chapa->points.push_back(cloud_msg->at(0,0));
    }

    for(int i=0; i<puntos_chapa->width; i++)
    {
        for(int j=0; j<puntos_chapa->height; j++)
        {

            pcl::PointXYZRGB point = cloud_msg->at(range_x[i],range_y[j]);
            int j_i = j-cloud_msg->height/2;
            puntos_chapa->at(i,j) = point;

        }
    }

    cv::Mat img_puntos_chapa = cv::Mat::zeros(puntos_chapa->height, puntos_chapa->width, CV_8UC3);
    cv::Mat data_svd = cv::Mat::ones(puntos_chapa->height*puntos_chapa->width, 4, CV_32F);

    int n_nan = 0;
    for (int i=0;i<data_svd.rows;i++)
    {
        int fila = i/puntos_chapa->width;
        int columna = i%puntos_chapa->width;


        pcl::PointXYZRGB point = puntos_chapa->at(columna,fila);
        Eigen::Vector3i rgb = point.getRGBVector3i();

        img_puntos_chapa.at<cv::Vec3b>(fila, columna)[0] = rgb[2];
        img_puntos_chapa.at<cv::Vec3b>(fila, columna)[1] = rgb[1];
        img_puntos_chapa.at<cv::Vec3b>(fila, columna)[2] = rgb[0];

        if (std::isnan(point.x))
        {
            n_nan++;
        }

        data_svd.at<float>(i,0) = point.x;
        data_svd.at<float>(i,1) = point.y;
        data_svd.at<float>(i,2) = point.z;
    }

       cv::Mat puntos_sinNan(data_svd.rows-n_nan,4,CV_32F);
       int indice = 0;
       for (int i=0; i<data_svd.rows;i++)
       {
           if (!std::isnan(data_svd.at<float>(i,0)))
           {
               puntos_sinNan.at<float>(indice,0)=data_svd.at<float>(i,0);
               puntos_sinNan.at<float>(indice,1)=data_svd.at<float>(i,1);
               puntos_sinNan.at<float>(indice,2)=data_svd.at<float>(i,2);
               puntos_sinNan.at<float>(indice,3)=1;

               indice++;
           }
       }


    //Ajustamos los datos resolviendo la ecuación: La solución buscada es la última columna de la matriz V que resulta al hacer la descomposición SVD de la matriz de coeficientes del sistema.
    cv::Mat U,D,V;
    cv::SVD::compute(puntos_sinNan,U,D,V);
    plano = (V.row(V.rows-1)).t();
    std::cout << plano << std::endl;

    //Calculamos el error
    cv::Mat error;//(puntos_sinNan.rows,1,CV_32F);
    error = puntos_sinNan*plano;
    //std::cout << error<< std::endl;

    //Usaremos la desviación típica para calcular el margen de error
    cv::Scalar mean, stddev;
    cv::meanStdDev(error, mean, stddev);
    sig = stddev[0];
    double minerr,maxerr;
    cv::minMaxLoc(cv::abs(error),&minerr,&maxerr);

    std::cout << "SIG: " << sig << std::endl;
    isTransformKnown = true;


    /// Comprobación del plano obtenido con imágenes de depuración
    std::fstream f_;
       f_.open("/home/irobot/datos/realsenseTrasera/2/pointcloud.txt",std::fstream::in);
       std::vector<std::vector<float>> datos_;

       if (!f_.is_open())
       {
           ROS_INFO("No se han encontrado los datos de depuración.");
           return;
       }

       if (f_.is_open())
        {
          std::string line;
          while (std::getline(f_,line))
          {
            std::istringstream ss( line );
            std::vector <std::string> record;
            std::vector<float> data_aux;
            while (ss)
            {
             std::string s;
             if (!std::getline( ss, line, ' ' )) break;
             data_aux.push_back(atof(line.c_str()));

            }
                datos_.push_back(data_aux);

          }
          f_.close();
        }

       cv::Mat puntos_(datos_.size(),4,CV_32F);

       for (int i=0; i<datos_.size();i++)
       {
           puntos_.at<float>(i,0)=datos_[i][0];
           puntos_.at<float>(i,1)=datos_[i][1];
           puntos_.at<float>(i,2)=datos_[i][2];
           puntos_.at<float>(i,3)=1;

           if (std::isnan(datos_[i][0]))
           {
               puntos_.at<float>(i,0)=0;
               puntos_.at<float>(i,1)=0;
               puntos_.at<float>(i,2)=0;
           }
       }

       cv::Mat img = cv::imread("/home/irobot/datos/realsenseDelantera/2/rgb.png");
       cv::Mat dist_plano = puntos_*plano; // calculo de la distancia al plano de la chapa

       cv::Mat dist_plano_i(img.rows,img.cols,CV_32F);
       for (int i=0; i<dist_plano.rows;i++)
       {
           int fila = i/dist_plano_i.cols;
           int columna = i%dist_plano_i.cols;
           dist_plano_i.at<float>(fila,columna) = dist_plano.at<float>(i,0);
       }


       float alpha = 3;
       dist_plano_i = cv::abs(dist_plano_i) < alpha*sig;

       cv::Mat img_homography_;
       warpPerspective(dist_plano_i,img_homography_,H2,cv::Size(1500,1000)); //Ajustar el tamaño

       cv::namedWindow("DIST", cv::WINDOW_NORMAL);
       cv::imshow("DIST",img_homography_);
       cv::waitKey(0);


    /////////////////


  }

  if (isTransformKnown)
  {
    // Guardar datos en archivo
    fs_ << "Homography" << H;
    fs_ << "Homography2" << H2;
    fs_ << "rel_m_pxls" << rel_m_pixls;
    fs_ << "plano" << plano;
    fs_ << "std" << sig;
    fs_.release();

    /// Creación archivo .h con los datos obtenidos
    std::stringstream aux;
    aux << "_" << camera_name;

    std::fstream f_header;
    std::stringstream name_file_;
    name_file_ << "/home/irobot/homography" << aux.str() << ".h";
    f_header.open(name_file_.str(),std::fstream::in | std::fstream::out | std::fstream::trunc);
    f_header << "#include <opencv2/opencv.hpp>" << std::endl;

    f_header << "namespace homography" <<aux.str()<<std::endl << "{"<<std::endl;
    writeMat(f_header,H,"H");
    writeMat(f_header,H2,"H2");
    writeFloat(f_header,rel_m_pixls,"rel_m_pxl");
    writeMat(f_header,plano,"plano");
    writeFloat(f_header,sig,"std");
    f_header << "}";

    f_header.close();

    ROS_INFO_STREAM("Datos guardados correctamente en..." << file_name);
    mySigintHandler(1);
  }

  cv::waitKey(1);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "homography_calibration");
  ros::NodeHandle nh;

  id_marker_calib = 0;
  file_name = "/home/irobot/data.yml";
  size_marker = 0.2;
  camera_topic = "/summit_xl/front_realsense";
  camera_name = "front";

  ros::param::get("~id_marker", id_marker_calib);
  ros::param::get("~path_file", file_name);
  ros::param::get("~size_marker", size_marker);
  ros::param::get("~camera_topic", camera_topic);
  ros::param::get("~camera_name", camera_name);

  std::stringstream topic;
  topic << camera_topic <<"/color/image_raw";

  ROS_INFO_STREAM("RGB topic:" << topic.str());
  ros::Subscriber sub = nh.subscribe(topic.str(), 1000, callback);

  ROS_INFO("Homography calibration ready!");

  ROS_INFO("Id Marker: %d", id_marker_calib);
  ROS_INFO("Size Marker: %f", size_marker);
  ROS_INFO_STREAM("Camera topic:" << camera_topic);
  ROS_INFO_STREAM("Path file:" << file_name);

  ros::spin();

  return 0;
}
