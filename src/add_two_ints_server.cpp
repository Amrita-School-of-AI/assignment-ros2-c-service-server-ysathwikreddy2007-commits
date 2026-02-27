#include <memory>
#include <functional>

#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"

using std::placeholders::_1;
using std::placeholders::_2;

class AddTwoIntsServer : public rclcpp::Node
{
public:
    AddTwoIntsServer()
        : Node("add_two_ints_server")
    {
        // Create the service named "add_two_ints" using example_interfaces::srv::AddTwoInts
        service_ = this->create_service<example_interfaces::srv::AddTwoInts>(
            "add_two_ints", 
            std::bind(&AddTwoIntsServer::handle_add_two_ints, this, _1, _2));
    }

private:
    // Service callback function to process requests
    void handle_add_two_ints(
        const std::shared_ptr<example_interfaces::srv::AddTwoInts::Request> request,
        std::shared_ptr<example_interfaces::srv::AddTwoInts::Response> response)
    {
        // Add the two integers from the request
        response->sum = request->a + request->b;

        // Log the incoming request and the calculated result
        RCLCPP_INFO(this->get_logger(), "Incoming request: a=%ld, b=%ld", request->a, request->b);
        RCLCPP_INFO(this->get_logger(), "Sending response: sum=%ld", response->sum);
    }

    rclcpp::Service<example_interfaces::srv::AddTwoInts>::SharedPtr service_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<AddTwoIntsServer>());
    rclcpp::shutdown();
    return 0;
}