#include <iostream>
#include <mutex>
#include <thread>

struct connection_info {};
struct connection_handle {
  void send_data(data_package const& data) {}
  data_package receive_data() {}
};
struct connection_manager {};
struct data_package {};

class x {
 private:
  connection_info connection_details;
  connection_handle connection;
  std::once_flag connection_init_flag;
  void open_connection() {
    connection = connection_manager.open(connection_details);
  }

 public:
  x(connection_info const& connection_details_)
      : connection_details(connection_details_) {}

  /**
   * @brief
   * init will be done either by the first call to send_data
   * or by the first call to receive_data
   */
  void send_data(data_package const& data) {
    std::call_once(connection_init_flag, &x::open_connection, this);
    connection.send_data(data);
  }

  data_package receive_data() {
    std::call_once(connection_init_flag, &x::open_connection, this);
    return connection.receive_data();
  }
};  // x