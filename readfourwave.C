#include <iostream>
#include <vector>
#include <cstring>
#include <lxi.h>
#include <TGraph.h>
#include <TCanvas.h>

int main()
{
  std::stringstream ss_loadlib;
  std::string wkfd = gSystem->WorkingDirectory();
  ss_loadlib << wkfd.c_str() << "/../../../INSTALL/lib/" << "librootlxi.so";
  std::cout << "loading external rootlib: " << ss_loadlib.str() << std::endl;
  gSystem->Load(ss_loadlib.str().c_str());

  const char command_Stop[] = ":STOP";                          ///STOP  RUN
  const char command_setsource[] = ":WAVeform:SOURce CHANnel1"; /// Set wave source
  const char command_setsource2[] = ":WAVeform:SOURce CHANnel2"; /// Set wave source 2
  const char command_setsource3[] = ":WAVeform:SOURce CHANnel3"; /// Set wave source 2
  const char command_setsource4[] = ":WAVeform:SOURce CHANnel4"; /// Set wave source 2
  const char command_formatset[] = ":WAV:FORM WORD";            /// WORD  BYTE  ASCii
  const char command_set_mode[] =  ":WAVeform:MODE NORMAL";        /// NORMal MAXimum RAW
  const char command_set_scale[] = ":CHANnel1:SCALe 1 ";        /// Set CHANnel1 scale
  const char command_return_scale[] = ":CHANnel1:SCALe?";       /// Query CHANnel1 scale
  const char command_return_mode[] = ":WAVeform:MODE?";         /// Query the waveform mode
  const char command_returnsource[] = ":WAVeform:SOURce?";      /// Query wave source
  const char command_format[] = ":WAVeform:FORMat?";            /// Query the return format of the waveform
  const char command_set_point[] = ":WAVeform:POINts 1000";     /// Set number of points
  const char command_points[] = ":WAVeform:POINts?";            /// return the number of Points
  const char command_set_start[] = ":WAVeform:STARt 1";       /// Set the start point
  const char command_return_start[] = ":WAVeform:STARt?";       /// Query the start point
  const char command_set_stop[] = ":WAVeform:STOP 1000";        /// Set the stop point
  const char command_return_stop[] = ":WAVeform:STOP?";         /// Query the stop point
  const char command_x_increment[] = ":WAVeform:XINCrement?";   /// Time interval between two adjacent points in the X direction
  const char command_y_increment[] = ":WAVeform:YINCrement?";   /// Query the unit voltage in the Y direction of the current channel source.
  const char command_x_origin[] = ":WAVeform:XORigin?";         /// Start time of waveform data in the X direction.
  const char command_y_origin[] = ":WAVeform:YORigin?";         /// The vertical offset in the Y direction relative to the vertical reference position
  const char command_x_reference[] = ":WAVeform:XREFerence?";   /// Return XREFerence
  const char command_y_reference[] = ":WAVeform:YREFerence?";   /// Return YREFerence
  const char command_waveform_data[] = ":WAVeform:DATA?";       /// Acquire wave data

  char response_format[256];
  char response_mode[256];
  char response_scale[256];
  char response_points[256];
  char response_start[256];
  char response_stop[256];
  char response_wave_source[256];
  char response_x_increment[256];
  char response_y_increment[256];
  char response_x_origin[256];
  char response_y_origin[256];
  char response_x_reference[256];
  char response_y_reference[256];
  char response_waveform_data[65536*64];

  int device, timeout = 3000;

  // Initial  LXI device
  lxi_init();
  device = lxi_connect("192.168.21.110", 0, "inst0", timeout, VXI11);

  // STOP
  lxi_send(device, command_Stop, sizeof(command_Stop), timeout);

  // Set wave source
  lxi_send(device, command_setsource, sizeof(command_setsource), timeout);

  // Query wave source
  memset(response_wave_source, 0, sizeof(response_wave_source));
  lxi_send(device, command_returnsource, sizeof(command_returnsource), timeout);
  lxi_receive(device, response_wave_source, sizeof(response_wave_source), timeout);
  std::cout << "response_wave_source: " << response_wave_source << std::endl;

  // Set wave form mode
  lxi_send(device, command_set_mode, sizeof(command_set_mode), timeout);

  // Query the return mode of the waveform
  memset(response_mode, 0, sizeof(response_mode));
  lxi_send(device, command_return_mode, sizeof(command_return_mode), timeout);
  lxi_receive(device, response_mode, sizeof(response_mode), timeout);
  std::cout << "response_mode: " << response_mode << std::endl;

  // Set CHANNEL1 scale
  //lxi_send(device, command_set_scale, sizeof(command_set_scale), timeout);

  // Query the return scale of the waveform
  memset(response_scale, 0, sizeof(response_scale));
  lxi_send(device, command_return_scale, sizeof(command_return_scale), timeout);
  lxi_receive(device, response_scale, sizeof(response_scale), timeout);
  std::cout << "response_scale: " << response_scale << std::endl;

  // Set wave form
  lxi_send(device, command_formatset, sizeof(command_formatset), timeout);

  // Query the return format of the waveform
  memset(response_format, 0, sizeof(response_format));
  lxi_send(device, command_format, sizeof(command_format), timeout);
  lxi_receive(device, response_format, sizeof(response_format), timeout);
  std::string format(response_format); // Save wave format

  // Set the number of points
  //lxi_send(device, command_set_point, sizeof(command_set_point), timeout);

  // return the number of Points
  memset(response_points, 0, sizeof(response_points));
  lxi_send(device, command_points, sizeof(command_points), timeout);
  lxi_receive(device, response_points, sizeof(response_points), timeout);
  int points = atoi(response_points); // save the number of points
  std::cout << "Number of points: " << points << std::endl;

  //Set Satrt point
  lxi_send(device, command_set_start, sizeof(command_set_start), timeout);

  // Return the start point
  memset(response_start, 0, sizeof(response_start));
  lxi_send(device, command_return_start, sizeof(command_return_start), timeout);
  lxi_receive(device, response_start, sizeof(response_start), timeout);
  int start_point = atoi(response_start); // save the start point
  std::cout << "Start point: " << start_point << std::endl;

  // Set the end point
  lxi_send(device, command_set_stop, sizeof(command_set_stop), timeout);

  // Return the end point
  memset(response_stop, 0, sizeof(response_stop));
  lxi_send(device, command_return_stop, sizeof(command_return_stop), timeout);
  lxi_receive(device, response_stop, sizeof(response_stop), timeout);
  int end_point = atoi(response_stop); // save the end point
  std::cout << "End point: " << end_point << std::endl;

  // Time interval between two adjacent points in the X direction
  memset(response_x_increment, 0, sizeof(response_x_increment));
  lxi_send(device, command_x_increment, sizeof(command_x_increment), timeout);
  lxi_receive(device, response_x_increment, sizeof(response_x_increment), timeout);
  double x_increment = atof(response_x_increment); // X

  // Query the unit voltage in the Y direction of the current channel source.
  memset(response_y_increment, 0, sizeof(response_y_increment));
  lxi_send(device, command_y_increment, sizeof(command_y_increment), timeout);
  lxi_receive(device, response_y_increment, sizeof(response_y_increment), timeout);
  double y_increment = atof(response_y_increment); // Y
  std::cout << "response_y_increment: " << response_y_increment << std::endl;
  std::cout << "y_increment: " << y_increment << std::endl;

  // Start time of waveform data in the X direction.
  memset(response_x_origin, 0, sizeof(response_x_origin));
  lxi_send(device, command_x_origin, sizeof(command_x_origin), timeout);
  lxi_receive(device, response_x_origin, sizeof(response_x_origin), timeout);
  double x_origin = atof(response_x_origin); // X start
  std::cout << "x_origin: " << x_origin << std::endl;
  /*for (int i=0;i<sizeof(response_x_origin);i++)
  {
    std::cout<<" response_x_origin: "<<response_x_origin[i]<<std::endl;
  }*/

  // The vertical offset in the Y direction relative to the vertical reference position
  memset(response_y_origin, 0, sizeof(response_y_origin));
  lxi_send(device, command_y_origin, sizeof(command_y_origin), timeout);
  lxi_receive(device, response_y_origin, sizeof(response_y_origin), timeout);
  double y_origin = atof(response_y_origin); // Y
  std::cout << "y_origin: " << y_origin << std::endl;

  //return XREFerence
  memset(response_x_reference, 0, sizeof(response_x_reference));
  lxi_send(device, command_x_reference, sizeof(command_x_reference), timeout);
  lxi_receive(device, response_x_reference, sizeof(response_x_reference), timeout);
  std::cout << "x_reference: " << response_x_reference << std::endl;
  double x_reference = atof(response_x_reference); // X start
  std::cout << "x_reference: " << x_reference << std::endl;

  // return YREFerence
  memset(response_y_reference, 0, sizeof(response_y_reference));
  lxi_send(device, command_y_reference, sizeof(command_y_reference), timeout);
  lxi_receive(device, response_y_reference, sizeof(response_y_reference), timeout);
  double y_reference = atof(response_y_reference);
  std::cout << "y_reference: " << y_reference << std::endl;
  std::cout << "response_y_reference: " << response_y_reference << std::endl;

  // acquire wave data
  memset(response_waveform_data, 0, sizeof(response_waveform_data));
  lxi_send(device, command_waveform_data, sizeof(command_waveform_data), timeout);
  lxi_receive(device, response_waveform_data, sizeof(response_waveform_data), timeout);
  // for (int i=0;i<100/*sizeof(response_waveform_data)*/;i++){
  // std::cout<<"response_waveform_data: "<<response_waveform_data[i]<<std::endl;
  //}
  // Check if it contain TMC
  int data_offset = 0;
  if (response_waveform_data[0] == '#')
  {
    std::cout << "response_waveform_data[1]: " << response_waveform_data[1] << std::endl;
    int header_length = response_waveform_data[1] - '0'; // Length of TMC
    std::cout << "header_length: " << header_length << std::endl;
    int data_length = atoi(std::string(&response_waveform_data[2], header_length).c_str()); // return data length
    data_offset = 2 + header_length;                                                        // Skip TMC
    std::cout << "Data length from TMC header: " << data_length << std::endl;
  }

  // initial draw x y
  std::vector<double> x(points), y(points);

  // judg data format and draw
  if (format.find("WORD") != std::string::npos)
  {
    // WORD
    for (int i = start_point-1; i < end_point; i++)
    {
      // 16-bit    1point 2byte
      uint8_t word_value = (response_waveform_data[data_offset + 2 * i]);
      // std::cout<<"word_value: "<<word_value<<std::endl;
      //y[i] = (word_value - y_origin - y_reference) * y_increment;
      y[i] = (word_value - y_origin - y_reference) * y_increment;
      x[i] = i * x_increment + x_origin; // time axis
      //std::cout << "x[i]: " << x[i] <<" y[i]: "<<y[i]<< std::endl;
    }
    /*std::cout<<"response_waveform_data[data_offset + 0]: "<<(void*) &response_waveform_data[data_offset +0]<<std::endl;
    std::cout<<"response_waveform_data[data_offset + 1]: "<<(void*) &response_waveform_data[data_offset +1]<<std::endl;
    std::cout<<"response_waveform_data[data_offset + 2]: "<<(void*) &(response_waveform_data[data_offset +2])<<std::endl;*/
    // test it is big or little endian
  }
  else if (format.find("BYTE") != std::string::npos)
  {
    // BYTE
    for (int i = 0; i < points; i++)
    {
      // 8-bit ，1point 1byte
      uint8_t byte_value = response_waveform_data[data_offset + i];
      y[i] = (byte_value - y_origin - y_reference) * y_increment;
      x[i] = i * x_increment + x_origin; // time axis
    }
  }
  else if (format.find("ASC") != std::string::npos)
  {
    // ASCii
    char *token = strtok(response_waveform_data + data_offset, ",");
    for (int i = 0; i < points && token != nullptr; i++)
    {
      y[i] = atof(token); // ASCii format is real voltage
      std::cout << "y[i]: " << y[i] << std::endl;
      // std::cout<<"response_waveform_data[i]: "<<response_waveform_data[i]<<std::endl;
      x[i] = i * x_increment + x_origin; // time axis
      token = strtok(nullptr, ",");
    }
  }
  else
  {
    std::cerr << "Unknown waveform format: " << format << std::endl;
    return 1;
  }




  // Set wave source
  lxi_send(device, command_setsource2, sizeof(command_setsource2), timeout);

  // Query wave source
  memset(response_wave_source, 0, sizeof(response_wave_source));
  lxi_send(device, command_returnsource, sizeof(command_returnsource), timeout);
  lxi_receive(device, response_wave_source, sizeof(response_wave_source), timeout);
  std::cout << "response_wave_source: " << response_wave_source << std::endl;

  // Set wave form mode
  lxi_send(device, command_set_mode, sizeof(command_set_mode), timeout);

  // Query the return mode of the waveform
  memset(response_mode, 0, sizeof(response_mode));
  lxi_send(device, command_return_mode, sizeof(command_return_mode), timeout);
  lxi_receive(device, response_mode, sizeof(response_mode), timeout);
  std::cout << "response_mode: " << response_mode << std::endl;

  // Set CHANNEL1 scale
  //lxi_send(device, command_set_scale, sizeof(command_set_scale), timeout);

  // Query the return scale of the waveform
  memset(response_scale, 0, sizeof(response_scale));
  lxi_send(device, command_return_scale, sizeof(command_return_scale), timeout);
  lxi_receive(device, response_scale, sizeof(response_scale), timeout);
  std::cout << "response_scale: " << response_scale << std::endl;

  // Set wave form
  lxi_send(device, command_formatset, sizeof(command_formatset), timeout);

  // Query the return format of the waveform
  memset(response_format, 0, sizeof(response_format));
  lxi_send(device, command_format, sizeof(command_format), timeout);
  lxi_receive(device, response_format, sizeof(response_format), timeout);
  std::string format2(response_format); // Save wave format

  // Set the number of points
  //lxi_send(device, command_set_point, sizeof(command_set_point), timeout);

  // return the number of Points
  memset(response_points, 0, sizeof(response_points));
  lxi_send(device, command_points, sizeof(command_points), timeout);
  lxi_receive(device, response_points, sizeof(response_points), timeout);
  int points2 = atoi(response_points); // save the number of points
  std::cout << "Number of points: " << points2 << std::endl;

  //Set Satrt point
  lxi_send(device, command_set_start, sizeof(command_set_start), timeout);

  // Return the start point
  memset(response_start, 0, sizeof(response_start));
  lxi_send(device, command_return_start, sizeof(command_return_start), timeout);
  lxi_receive(device, response_start, sizeof(response_start), timeout);
  int start_point2 = atoi(response_start); // save the start point
  std::cout << "Start point: " << start_point2 << std::endl;

  // Set the end point
  lxi_send(device, command_set_stop, sizeof(command_set_stop), timeout);

  // Return the end point
  memset(response_stop, 0, sizeof(response_stop));
  lxi_send(device, command_return_stop, sizeof(command_return_stop), timeout);
  lxi_receive(device, response_stop, sizeof(response_stop), timeout);
  int end_point2 = atoi(response_stop); // save the end point
  std::cout << "End point: " << end_point2 << std::endl;

  // Time interval between two adjacent points in the X direction
  memset(response_x_increment, 0, sizeof(response_x_increment));
  lxi_send(device, command_x_increment, sizeof(command_x_increment), timeout);
  lxi_receive(device, response_x_increment, sizeof(response_x_increment), timeout);
  double x_increment2 = atof(response_x_increment); // X

  // Query the unit voltage in the Y direction of the current channel source.
  memset(response_y_increment, 0, sizeof(response_y_increment));
  lxi_send(device, command_y_increment, sizeof(command_y_increment), timeout);
  lxi_receive(device, response_y_increment, sizeof(response_y_increment), timeout);
  double y_increment2 = atof(response_y_increment); // Y
  std::cout << "response_y_increment: " << response_y_increment << std::endl;
  std::cout << "y_increment: " << y_increment2 << std::endl;

  // Start time of waveform data in the X direction.
  memset(response_x_origin, 0, sizeof(response_x_origin));
  lxi_send(device, command_x_origin, sizeof(command_x_origin), timeout);
  lxi_receive(device, response_x_origin, sizeof(response_x_origin), timeout);
  double x_origin2 = atof(response_x_origin); // X start
  std::cout << "x_origin: " << x_origin2 << std::endl;
  /*for (int i=0;i<sizeof(response_x_origin);i++)
  {
    std::cout<<" response_x_origin: "<<response_x_origin[i]<<std::endl;
  }*/

  // The vertical offset in the Y direction relative to the vertical reference position
  memset(response_y_origin, 0, sizeof(response_y_origin));
  lxi_send(device, command_y_origin, sizeof(command_y_origin), timeout);
  lxi_receive(device, response_y_origin, sizeof(response_y_origin), timeout);
  double y_origin2 = atof(response_y_origin); // Y
  std::cout << "y_origin: " << y_origin2 << std::endl;

  //return XREFerence
  memset(response_x_reference, 0, sizeof(response_x_reference));
  lxi_send(device, command_x_reference, sizeof(command_x_reference), timeout);
  lxi_receive(device, response_x_reference, sizeof(response_x_reference), timeout);
  std::cout << "x_reference: " << response_x_reference << std::endl;
  double x_reference2 = atof(response_x_reference); // X start
  std::cout << "x_reference: " << x_reference2 << std::endl;

  // return YREFerence
  memset(response_y_reference, 0, sizeof(response_y_reference));
  lxi_send(device, command_y_reference, sizeof(command_y_reference), timeout);
  lxi_receive(device, response_y_reference, sizeof(response_y_reference), timeout);
  double y_reference2 = atof(response_y_reference);
  std::cout << "y_reference: " << y_reference2 << std::endl;
  std::cout << "response_y_reference: " << response_y_reference << std::endl;

  // acquire wave data
  memset(response_waveform_data, 0, sizeof(response_waveform_data));
  lxi_send(device, command_waveform_data, sizeof(command_waveform_data), timeout);
  lxi_receive(device, response_waveform_data, sizeof(response_waveform_data), timeout);
  // for (int i=0;i<100/*sizeof(response_waveform_data)*/;i++){
  // std::cout<<"response_waveform_data: "<<response_waveform_data[i]<<std::endl;
  //}
  // Check if it contain TMC
  int data_offset2 = 0;
  if (response_waveform_data[0] == '#')
  {
    std::cout << "response_waveform_data[1]: " << response_waveform_data[1] << std::endl;
    int header_length = response_waveform_data[1] - '0'; // Length of TMC
    std::cout << "header_length: " << header_length << std::endl;
    int data_length = atoi(std::string(&response_waveform_data[2], header_length).c_str()); // return data length
    data_offset = 2 + header_length;                                                        // Skip TMC
    std::cout << "Data length from TMC header: " << data_length << std::endl;
  }

  // initial draw x y
  std::vector<double> x2(points), y2(points);

  // judg data format and draw
  if (format.find("WORD") != std::string::npos)
  {
    // WORD
    for (int i = start_point2-1; i < end_point2; i++)
    {
      // 16-bit    1point 2byte
      uint8_t word_value = (response_waveform_data[data_offset + 2 * i]);
      // std::cout<<"word_value: "<<word_value<<std::endl;
      //y[i] = (word_value - y_origin - y_reference) * y_increment;
      y2[i] = (word_value - y_origin2 - y_reference) * y_increment2;
      x2[i] = i * x_increment2 + x_origin2; // time axis
      //std::cout << "x[i]: " << x[i] <<" y[i]: "<<y[i]<< std::endl;
    }
    /*std::cout<<"response_waveform_data[data_offset + 0]: "<<(void*) &response_waveform_data[data_offset +0]<<std::endl;
    std::cout<<"response_waveform_data[data_offset + 1]: "<<(void*) &response_waveform_data[data_offset +1]<<std::endl;
    std::cout<<"response_waveform_data[data_offset + 2]: "<<(void*) &(response_waveform_data[data_offset +2])<<std::endl;*/
    // test it is big or little endian
  }
  else if (format.find("BYTE") != std::string::npos)
  {
    // BYTE
    for (int i = 0; i < points2; i++)
    {
      // 8-bit ，1point 1byte
      uint8_t byte_value = response_waveform_data[data_offset + i];
      y2[i] = (byte_value - y_origin2 - y_reference2) * y_increment2;
      x2[i] = i * x_increment2 + x_origin2; // time axis
    }
  }
  else if (format.find("ASC") != std::string::npos)
  {
    // ASCii
    char *token = strtok(response_waveform_data + data_offset, ",");
    for (int i = 0; i < points2 && token != nullptr; i++)
    {
      y2[i] = atof(token); // ASCii format is real voltage
      std::cout << "y[i]: " << y2[i] << std::endl;
      // std::cout<<"response_waveform_data[i]: "<<response_waveform_data[i]<<std::endl;
      x2[i] = i * x_increment2 + x_origin2; // time axis
      token = strtok(nullptr, ",");
    }
  }
  else
  {
    std::cerr << "Unknown waveform format: " << format << std::endl;
    return 1;
  }



  // Set wave source
  lxi_send(device, command_setsource4, sizeof(command_setsource4), timeout);

  // Query wave source
  memset(response_wave_source, 0, sizeof(response_wave_source));
  lxi_send(device, command_returnsource, sizeof(command_returnsource), timeout);
  lxi_receive(device, response_wave_source, sizeof(response_wave_source), timeout);
  std::cout << "response_wave_source: " << response_wave_source << std::endl;

  // Set wave form mode
  lxi_send(device, command_set_mode, sizeof(command_set_mode), timeout);

  // Query the return mode of the waveform
  memset(response_mode, 0, sizeof(response_mode));
  lxi_send(device, command_return_mode, sizeof(command_return_mode), timeout);
  lxi_receive(device, response_mode, sizeof(response_mode), timeout);
  std::cout << "response_mode: " << response_mode << std::endl;

  // Set CHANNEL1 scale
  //lxi_send(device, command_set_scale, sizeof(command_set_scale), timeout);

  // Query the return scale of the waveform
  memset(response_scale, 0, sizeof(response_scale));
  lxi_send(device, command_return_scale, sizeof(command_return_scale), timeout);
  lxi_receive(device, response_scale, sizeof(response_scale), timeout);
  std::cout << "response_scale: " << response_scale << std::endl;

  // Set wave form
  lxi_send(device, command_formatset, sizeof(command_formatset), timeout);

  // Query the return format of the waveform
  memset(response_format, 0, sizeof(response_format));
  lxi_send(device, command_format, sizeof(command_format), timeout);
  lxi_receive(device, response_format, sizeof(response_format), timeout);
  std::string format4(response_format); // Save wave format

  // Set the number of points
  //lxi_send(device, command_set_point, sizeof(command_set_point), timeout);

  // return the number of Points
  memset(response_points, 0, sizeof(response_points));
  lxi_send(device, command_points, sizeof(command_points), timeout);
  lxi_receive(device, response_points, sizeof(response_points), timeout);
  int points4 = atoi(response_points); // save the number of points
  std::cout << "Number of points: " << points4 << std::endl;

  //Set Satrt point
  lxi_send(device, command_set_start, sizeof(command_set_start), timeout);

  // Return the start point
  memset(response_start, 0, sizeof(response_start));
  lxi_send(device, command_return_start, sizeof(command_return_start), timeout);
  lxi_receive(device, response_start, sizeof(response_start), timeout);
  int start_point4 = atoi(response_start); // save the start point
  std::cout << "Start point: " << start_point4 << std::endl;

  // Set the end point
  lxi_send(device, command_set_stop, sizeof(command_set_stop), timeout);

  // Return the end point
  memset(response_stop, 0, sizeof(response_stop));
  lxi_send(device, command_return_stop, sizeof(command_return_stop), timeout);
  lxi_receive(device, response_stop, sizeof(response_stop), timeout);
  int end_point4 = atoi(response_stop); // save the end point
  std::cout << "End point: " << end_point4 << std::endl;

  // Time interval between two adjacent points in the X direction
  memset(response_x_increment, 0, sizeof(response_x_increment));
  lxi_send(device, command_x_increment, sizeof(command_x_increment), timeout);
  lxi_receive(device, response_x_increment, sizeof(response_x_increment), timeout);
  double x_increment4 = atof(response_x_increment); // X

  // Query the unit voltage in the Y direction of the current channel source.
  memset(response_y_increment, 0, sizeof(response_y_increment));
  lxi_send(device, command_y_increment, sizeof(command_y_increment), timeout);
  lxi_receive(device, response_y_increment, sizeof(response_y_increment), timeout);
  double y_increment4 = atof(response_y_increment); // Y
  std::cout << "response_y_increment: " << response_y_increment << std::endl;
  std::cout << "y_increment: " << y_increment4 << std::endl;

  // Start time of waveform data in the X direction.
  memset(response_x_origin, 0, sizeof(response_x_origin));
  lxi_send(device, command_x_origin, sizeof(command_x_origin), timeout);
  lxi_receive(device, response_x_origin, sizeof(response_x_origin), timeout);
  double x_origin4 = atof(response_x_origin); // X start
  std::cout << "x_origin: " << x_origin4 << std::endl;
  /*for (int i=0;i<sizeof(response_x_origin);i++)
  {
    std::cout<<" response_x_origin: "<<response_x_origin[i]<<std::endl;
  }*/

  // The vertical offset in the Y direction relative to the vertical reference position
  memset(response_y_origin, 0, sizeof(response_y_origin));
  lxi_send(device, command_y_origin, sizeof(command_y_origin), timeout);
  lxi_receive(device, response_y_origin, sizeof(response_y_origin), timeout);
  double y_origin4 = atof(response_y_origin); // Y
  std::cout << "y_origin: " << y_origin4 << std::endl;

  //return XREFerence
  memset(response_x_reference, 0, sizeof(response_x_reference));
  lxi_send(device, command_x_reference, sizeof(command_x_reference), timeout);
  lxi_receive(device, response_x_reference, sizeof(response_x_reference), timeout);
  std::cout << "x_reference: " << response_x_reference << std::endl;
  double x_reference4 = atof(response_x_reference); // X start
  std::cout << "x_reference: " << x_reference4 << std::endl;

  // return YREFerence
  memset(response_y_reference, 0, sizeof(response_y_reference));
  lxi_send(device, command_y_reference, sizeof(command_y_reference), timeout);
  lxi_receive(device, response_y_reference, sizeof(response_y_reference), timeout);
  double y_reference4 = atof(response_y_reference);
  std::cout << "y_reference: " << y_reference4 << std::endl;
  std::cout << "response_y_reference: " << response_y_reference << std::endl;

  // acquire wave data
  memset(response_waveform_data, 0, sizeof(response_waveform_data));
  lxi_send(device, command_waveform_data, sizeof(command_waveform_data), timeout);
  lxi_receive(device, response_waveform_data, sizeof(response_waveform_data), timeout);
  // for (int i=0;i<100/*sizeof(response_waveform_data)*/;i++){
  // std::cout<<"response_waveform_data: "<<response_waveform_data[i]<<std::endl;
  //}
  // Check if it contain TMC
  int data_offset4 = 0;
  if (response_waveform_data[0] == '#')
  {
    std::cout << "response_waveform_data[1]: " << response_waveform_data[1] << std::endl;
    int header_length = response_waveform_data[1] - '0'; // Length of TMC
    std::cout << "header_length: " << header_length << std::endl;
    int data_length = atoi(std::string(&response_waveform_data[2], header_length).c_str()); // return data length
    data_offset4 = 2 + header_length;                                                        // Skip TMC
    std::cout << "Data length from TMC header: " << data_length << std::endl;
  }

  // initial draw x y
  std::vector<double> x4(points), y4(points);

  // judg data format and draw
  if (format.find("WORD") != std::string::npos)
  {
    // WORD
    for (int i = start_point4-1; i < end_point4; i++)
    {
      // 16-bit    1point 2byte
      uint8_t word_value = (response_waveform_data[data_offset4 + 2 * i]);
      // std::cout<<"word_value: "<<word_value<<std::endl;
      //y[i] = (word_value - y_origin - y_reference) * y_increment;
      y4[i] = (word_value - y_origin4 - y_reference) * y_increment4;
      x4[i] = i * x_increment4 + x_origin4; // time axis
      //std::cout << "x[i]: " << x[i] <<" y[i]: "<<y[i]<< std::endl;
    }
    /*std::cout<<"response_waveform_data[data_offset + 0]: "<<(void*) &response_waveform_data[data_offset +0]<<std::endl;
    std::cout<<"response_waveform_data[data_offset + 1]: "<<(void*) &response_waveform_data[data_offset +1]<<std::endl;
    std::cout<<"response_waveform_data[data_offset + 2]: "<<(void*) &(response_waveform_data[data_offset +2])<<std::endl;*/
    // test it is big or little endian
  }
  else if (format.find("BYTE") != std::string::npos)
  {
    // BYTE
    for (int i = 0; i < points4; i++)
    {
      // 8-bit ，1point 1byte
      uint8_t byte_value = response_waveform_data[data_offset4 + i];
      y4[i] = (byte_value - y_origin4 - y_reference4) * y_increment4;
      x4[i] = i * x_increment4 + x_origin4; // time axis
    }
  }
  else if (format.find("ASC") != std::string::npos)
  {
    // ASCii
    char *token = strtok(response_waveform_data + data_offset4, ",");
    for (int i = 0; i < points4 && token != nullptr; i++)
    {
      y4[i] = atof(token); // ASCii format is real voltage
      std::cout << "y[i]: " << y4[i] << std::endl;
      // std::cout<<"response_waveform_data[i]: "<<response_waveform_data[i]<<std::endl;
      x4[i] = i * x_increment4 + x_origin4; // time axis
      token = strtok(nullptr, ",");
    }
  }
  else
  {
    std::cerr << "Unknown waveform format: " << format << std::endl;
    return 1;
  }


  // Set wave source
  lxi_send(device, command_setsource3, sizeof(command_setsource3), timeout);

  // Query wave source
  memset(response_wave_source, 0, sizeof(response_wave_source));
  lxi_send(device, command_returnsource, sizeof(command_returnsource), timeout);
  lxi_receive(device, response_wave_source, sizeof(response_wave_source), timeout);
  std::cout << "response_wave_source: " << response_wave_source << std::endl;

  // Set wave form mode
  lxi_send(device, command_set_mode, sizeof(command_set_mode), timeout);

  // Query the return mode of the waveform
  memset(response_mode, 0, sizeof(response_mode));
  lxi_send(device, command_return_mode, sizeof(command_return_mode), timeout);
  lxi_receive(device, response_mode, sizeof(response_mode), timeout);
  std::cout << "response_mode: " << response_mode << std::endl;

  // Set CHANNEL1 scale
  //lxi_send(device, command_set_scale, sizeof(command_set_scale), timeout);

  // Query the return scale of the waveform
  memset(response_scale, 0, sizeof(response_scale));
  lxi_send(device, command_return_scale, sizeof(command_return_scale), timeout);
  lxi_receive(device, response_scale, sizeof(response_scale), timeout);
  std::cout << "response_scale: " << response_scale << std::endl;

  // Set wave form
  lxi_send(device, command_formatset, sizeof(command_formatset), timeout);

  // Query the return format of the waveform
  memset(response_format, 0, sizeof(response_format));
  lxi_send(device, command_format, sizeof(command_format), timeout);
  lxi_receive(device, response_format, sizeof(response_format), timeout);
  std::string format3(response_format); // Save wave format

  // Set the number of points
  //lxi_send(device, command_set_point, sizeof(command_set_point), timeout);

  // return the number of Points
  memset(response_points, 0, sizeof(response_points));
  lxi_send(device, command_points, sizeof(command_points), timeout);
  lxi_receive(device, response_points, sizeof(response_points), timeout);
  int points3 = atoi(response_points); // save the number of points
  std::cout << "Number of points: " << points3 << std::endl;

  //Set Satrt point
  lxi_send(device, command_set_start, sizeof(command_set_start), timeout);

  // Return the start point
  memset(response_start, 0, sizeof(response_start));
  lxi_send(device, command_return_start, sizeof(command_return_start), timeout);
  lxi_receive(device, response_start, sizeof(response_start), timeout);
  int start_point3 = atoi(response_start); // save the start point
  std::cout << "Start point: " << start_point3 << std::endl;

  // Set the end point
  lxi_send(device, command_set_stop, sizeof(command_set_stop), timeout);

  // Return the end point
  memset(response_stop, 0, sizeof(response_stop));
  lxi_send(device, command_return_stop, sizeof(command_return_stop), timeout);
  lxi_receive(device, response_stop, sizeof(response_stop), timeout);
  int end_point3 = atoi(response_stop); // save the end point
  std::cout << "End point: " << end_point3 << std::endl;

  // Time interval between two adjacent points in the X direction
  memset(response_x_increment, 0, sizeof(response_x_increment));
  lxi_send(device, command_x_increment, sizeof(command_x_increment), timeout);
  lxi_receive(device, response_x_increment, sizeof(response_x_increment), timeout);
  double x_increment3 = atof(response_x_increment); // X

  // Query the unit voltage in the Y direction of the current channel source.
  memset(response_y_increment, 0, sizeof(response_y_increment));
  lxi_send(device, command_y_increment, sizeof(command_y_increment), timeout);
  lxi_receive(device, response_y_increment, sizeof(response_y_increment), timeout);
  double y_increment3 = atof(response_y_increment); // Y
  std::cout << "response_y_increment: " << response_y_increment << std::endl;
  std::cout << "y_increment: " << y_increment3 << std::endl;

  // Start time of waveform data in the X direction.
  memset(response_x_origin, 0, sizeof(response_x_origin));
  lxi_send(device, command_x_origin, sizeof(command_x_origin), timeout);
  lxi_receive(device, response_x_origin, sizeof(response_x_origin), timeout);
  double x_origin3 = atof(response_x_origin); // X start
  std::cout << "x_origin: " << x_origin3 << std::endl;
  /*for (int i=0;i<sizeof(response_x_origin);i++)
  {
    std::cout<<" response_x_origin: "<<response_x_origin[i]<<std::endl;
  }*/

  // The vertical offset in the Y direction relative to the vertical reference position
  memset(response_y_origin, 0, sizeof(response_y_origin));
  lxi_send(device, command_y_origin, sizeof(command_y_origin), timeout);
  lxi_receive(device, response_y_origin, sizeof(response_y_origin), timeout);
  double y_origin3 = atof(response_y_origin); // Y
  std::cout << "y_origin: " << y_origin3 << std::endl;

  //return XREFerence
  memset(response_x_reference, 0, sizeof(response_x_reference));
  lxi_send(device, command_x_reference, sizeof(command_x_reference), timeout);
  lxi_receive(device, response_x_reference, sizeof(response_x_reference), timeout);
  std::cout << "x_reference: " << response_x_reference << std::endl;
  double x_reference3 = atof(response_x_reference); // X start
  std::cout << "x_reference: " << x_reference3 << std::endl;

  // return YREFerence
  memset(response_y_reference, 0, sizeof(response_y_reference));
  lxi_send(device, command_y_reference, sizeof(command_y_reference), timeout);
  lxi_receive(device, response_y_reference, sizeof(response_y_reference), timeout);
  double y_reference3 = atof(response_y_reference);
  std::cout << "y_reference: " << y_reference3 << std::endl;
  std::cout << "response_y_reference: " << response_y_reference << std::endl;

  // acquire wave data
  memset(response_waveform_data, 0, sizeof(response_waveform_data));
  lxi_send(device, command_waveform_data, sizeof(command_waveform_data), timeout);
  lxi_receive(device, response_waveform_data, sizeof(response_waveform_data), timeout);
  // for (int i=0;i<100/*sizeof(response_waveform_data)*/;i++){
  // std::cout<<"response_waveform_data: "<<response_waveform_data[i]<<std::endl;
  //}
  // Check if it contain TMC
  int data_offset3 = 0;
  if (response_waveform_data[0] == '#')
  {
    std::cout << "response_waveform_data[1]: " << response_waveform_data[1] << std::endl;
    int header_length = response_waveform_data[1] - '0'; // Length of TMC
    std::cout << "header_length: " << header_length << std::endl;
    int data_length = atoi(std::string(&response_waveform_data[2], header_length).c_str()); // return data length
    data_offset3 = 2 + header_length;                                                        // Skip TMC
    std::cout << "Data length from TMC header: " << data_length << std::endl;
  }

  // initial draw x y
  std::vector<double> x3(points), y3(points);

  // judg data format and draw
  if (format.find("WORD") != std::string::npos)
  {
    // WORD
    for (int i = start_point3-1; i < end_point3; i++)
    {
      // 16-bit    1point 2byte
      uint8_t word_value = (response_waveform_data[data_offset3 + 2 * i]);
      // std::cout<<"word_value: "<<word_value<<std::endl;
      //y[i] = (word_value - y_origin - y_reference) * y_increment;
      y3[i] = (word_value - y_origin3 - y_reference) * y_increment3;
      x3[i] = i * x_increment3 + x_origin3; // time axis
      //std::cout << "x[i]: " << x[i] <<" y[i]: "<<y[i]<< std::endl;
    }
    /*std::cout<<"response_waveform_data[data_offset + 0]: "<<(void*) &response_waveform_data[data_offset +0]<<std::endl;
    std::cout<<"response_waveform_data[data_offset + 1]: "<<(void*) &response_waveform_data[data_offset +1]<<std::endl;
    std::cout<<"response_waveform_data[data_offset + 2]: "<<(void*) &(response_waveform_data[data_offset +2])<<std::endl;*/
    // test it is big or little endian
  }
  else if (format.find("BYTE") != std::string::npos)
  {
    // BYTE
    for (int i = 0; i < points3; i++)
    {
      // 8-bit ，1point 1byte
      uint8_t byte_value = response_waveform_data[data_offset3 + i];
      y3[i] = (byte_value - y_origin3 - y_reference3) * y_increment3;
      x3[i] = i * x_increment3 + x_origin3; // time axis
    }
  }
  else if (format.find("ASC") != std::string::npos)
  {
    // ASCii
    char *token = strtok(response_waveform_data + data_offset3, ",");
    for (int i = 0; i < points3 && token != nullptr; i++)
    {
      y3[i] = atof(token); // ASCii format is real voltage
      std::cout << "y[i]: " << y3[i] << std::endl;
      // std::cout<<"response_waveform_data[i]: "<<response_waveform_data[i]<<std::endl;
      x3[i] = i * x_increment3 + x_origin3; // time axis
      token = strtok(nullptr, ",");
    }
  }
  else
  {
    std::cerr << "Unknown waveform format: " << format << std::endl;
    return 1;
  }







  // Draw with ROOT
  TCanvas *c1 = new TCanvas("c1", "Waveform", 800, 600);
  c1->Divide(1,3);
  c1->cd(1);
  TGraph *graph = new TGraph(end_point-start_point+1, &x[0], &y[0]);
  graph->SetTitle("Discriminate Signal;Time (s);Voltage (V)");
  graph->SetMarkerStyle(7);
  graph->SetMarkerSize(1);
  graph->SetMarkerColor(kRed);
  graph->SetLineColor(kRed);
  graph->Draw("APL");

  //c1->cd(2);
  TGraph *graph2 = new TGraph(end_point-start_point+1, &x2[0], &y2[0]);
  graph2->SetTitle("Discriminate Signal;Time (s);Voltage (V)");
  graph2->SetMarkerStyle(7);
  graph2->SetMarkerSize(1);
  graph2->SetMarkerColor(kBlue);
  graph2->SetLineColor(kBlue);
  graph2->Draw("PLSame");
  c1->SaveAs("waveform.png");

  c1->cd(2);
  TGraph *graph3 = new TGraph(end_point-start_point+1, &x3[0], &y3[0]);
  graph3->SetTitle("Coincidence Signal;Time (s);Voltage (V)");
  graph3->SetMarkerStyle(7);
  graph3->SetMarkerSize(1);
  graph3->SetMarkerColor(kGreen);
  graph3->SetLineColor(kGreen);
  graph3->Draw("APL");
  c1->SaveAs("waveform.png");

  c1->cd(3);
  TGraph *graph4 = new TGraph(end_point-start_point+1, &x4[0], &y4[0]);
  graph4->SetTitle("RPC Signal;Time (s);Voltage (V)");
  graph4->SetMarkerStyle(7);
  graph4->SetMarkerSize(1);
  graph4->SetMarkerColor(7);
  graph4->SetLineColor(7);
  graph4->Draw("APL");
  c1->SaveAs("waveform.png");

  // disconnect
  lxi_disconnect(device);
  return 0;
}
