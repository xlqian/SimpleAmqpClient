#include <SimpleAmqpClient/SimpleAmqpClient.h>

#include <iostream>
#include <string>
#include <unistd.h>

using namespace AmqpClient;
using namespace std;

int main()
{
  Channel::ptr_t channel = Channel::Create("127.0.0.1");
  string queue = channel->DeclareQueue("");

  while (true)
  {
    try
    {
      sleep(3);
      channel->BasicPublish("", queue, BasicMessage::Create("This is awesome"));
      cout << "Message published.\n";
    }
    catch (...)
    {
      cout << "Connection lost... retrying...";
      while (true)
      {
        sleep(1);
        try
        {
          channel = Channel::Create("127.0.0.1");
          cout << "reconnected.\n";
          break;
        }
        catch (exception &e)
        {
          cout << "\nFailure to reconnect: " << e.what() << endl;
        }
      }
    }
  }
  return 0;
}
