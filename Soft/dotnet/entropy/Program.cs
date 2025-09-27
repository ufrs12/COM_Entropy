using System;
using System.IO;
using System.IO.Ports;
using System.Runtime.InteropServices;
using System.Linq;

class Program
{
    static void Main()
    {
        string[] ports;

        if (RuntimeInformation.IsOSPlatform(OSPlatform.Windows))
        {
            // На Windows используем стандартный метод
            ports = SerialPort.GetPortNames();
        }
        else if (RuntimeInformation.IsOSPlatform(OSPlatform.Linux))
        {
            // На Linux ищем устройства в /dev/, соответствующие терминальным устройствам
            var possiblePorts = Directory.GetFiles("/dev/")
                .Where(name => name.StartsWith("/dev/ttyS")    // стандартные последовательные порты
                             || name.StartsWith("/dev/ttyUSB")  // USB-to-serial конвертеры
                             || name.StartsWith("/dev/ttyACM")  // ACM-устройства (модемы, ардуино и др.)
                             || name.StartsWith("/dev/ttyAMA")  // Raspberry Pi и др.
                             || name.StartsWith("/dev/ttyAP"))  // другие варианты
                .ToArray();

            ports = possiblePorts;
        }
        else if (RuntimeInformation.IsOSPlatform(OSPlatform.OSX))
        {
            // На MacOS это обычно /dev/tty.* или /dev/cu.*
            var possiblePorts = Directory.GetFiles("/dev/")
                .Where(name => name.StartsWith("/dev/tty.") || name.StartsWith("/dev/cu."))
                .ToArray();

            ports = possiblePorts;
        }
        else
        {
            Console.WriteLine("Платформа не поддерживается.");
            return;
        }

        if (ports.Length == 0)
        {
            Console.WriteLine("Доступные последовательные порты не найдены.");
        }
        else
        {
            Console.WriteLine("Доступные последовательные порты:");
            foreach (var port in ports)
            {
                Console.WriteLine(port);
            }
        }

        Console.WriteLine("Нажмите любую клавишу для выхода...");
        Console.ReadKey();
    }
}