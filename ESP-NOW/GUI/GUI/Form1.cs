using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace GUI
{
    public partial class Form1 : Form
    {

        private bool isOn = false;
        private int xCounter = 1;

        public Form1()
        {
            InitializeComponent();

            buttonActuator1.Text = "OFF";
            buttonActuator1.BackColor = Color.Red;
            Actuator1.Image = Properties.Resources.LED_R;

            buttonActuator2.Text = "OFF";
            buttonActuator2.BackColor = Color.Red;
            Actuator2.Image = Properties.Resources.LED_R;

            foreach (Series series in DataPlot.Series)
            {
                series.Points.Clear();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            buttonOpen.Enabled = true;
            buttonClose.Enabled = false;
            progressBarConnection.Value = 0;
            pictureBoxN1.Image = Properties.Resources.LED_R;

            string[] portList = SerialPort.GetPortNames();
            comboBoxPort.Items.AddRange(portList);
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
            }
        }
        private void Form1_MouseEnter(object sender, EventArgs e)
        {

        }

        private void Form1_MouseLeave(object sender, EventArgs e)
        {

        }

        private void buttonOpen_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = comboBoxPort.Text;
                serialPort1.BaudRate = Convert.ToInt32(comboBoxBaudRate.Text);
                serialPort1.Open();

                buttonOpen.Enabled = false;
                buttonClose.Enabled = true;
                progressBarConnection.Value = 100;
                comboBoxBaudRate.Enabled = false;
                comboBoxPort.Enabled = false;
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }
        }

        private void buttonClose_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                try
                {
                    serialPort1.WriteLine("#Off");
                    pictureBoxN1.Image = Properties.Resources.LED_R;

                    serialPort1.Close();

                    buttonOpen.Enabled = true;
                    buttonClose.Enabled = false;
                    progressBarConnection.Value = 0;
                    comboBoxBaudRate.Enabled = true;
                    comboBoxPort.Enabled = true;
                }
                catch (Exception error)
                {
                    MessageBox.Show(error.Message);
                }
            }
        }

        private void DataPlot_Click(object sender, EventArgs e)
        {

        }

        private Queue<int> valueQueue1 = new Queue<int>();
        private Queue<int> valueQueue2 = new Queue<int>();
        private Queue<int> valueQueue3 = new Queue<int>();
        private Queue<int> valueQueue4 = new Queue<int>();

        private const int Factor = 100; // Puedes ajustar este factor según tus necesidades

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            while (serialPort1.IsOpen && serialPort1.BytesToRead > 0)
            {
                string serialData = serialPort1.ReadLine();
                string[] values = serialData.Split(',');

                if (values.Length == 4)
                {
                    float value1 = Convert.ToSingle(values[0]);
                    float value2 = Convert.ToSingle(values[1]);
                    float value3 = Convert.ToSingle(values[2]);
                    float value4 = Convert.ToSingle(values[3]);

                    int intValue1 = (int)(value1 / Factor);
                    int intValue2 = (int)(value2 / Factor);
                    int intValue3 = (int)(value3 / Factor);
                    int intValue4 = (int)(value4 / Factor);

                    // Update LED images
                    UpdateLEDImage(pictureBoxN1, intValue1);
                    UpdateLEDImage(pictureBoxN2, intValue2);
                    UpdateLEDImage(pictureBoxN3, intValue3);
                    UpdateLEDImage(pictureBoxN4, intValue4);

                    // Add values to the queues
                    valueQueue1.Enqueue(intValue1);
                    valueQueue2.Enqueue(intValue2);
                    valueQueue3.Enqueue(intValue3);
                    valueQueue4.Enqueue(intValue4);

                    // Remove the oldest values if any queue size exceeds 8
                    while (valueQueue1.Count > 8)
                    {
                        valueQueue1.Dequeue();
                        valueQueue2.Dequeue();
                        valueQueue3.Dequeue();
                        valueQueue4.Dequeue();
                    }

                    // Update the chart
                    UpdateChart();
                }
            }
        }

        private void UpdateLEDImage(PictureBox pictureBox, int value)
        {
            pictureBox.Invoke((MethodInvoker)(() =>
            {
                if (value > 0)
                {
                    pictureBox.Image = Properties.Resources.LED_G;
                }
                else
                {
                    pictureBox.Image = Properties.Resources.LED_R;
                }
            }));
        }

        private void UpdateChart()
        {
            DataPlot.Invoke((MethodInvoker)(() =>
            {
                DataPlot.Series["Node1"].Points.Clear();
                DataPlot.Series["Node2"].Points.Clear();
                DataPlot.Series["Node3"].Points.Clear();
                DataPlot.Series["Node4"].Points.Clear();

                DateTime time = DateTime.Now;

                foreach (int value in valueQueue1)
                {
                    DataPlot.Series["Node1"].Points.AddXY(time, value);
                    time = time.AddSeconds(1); // Assuming a new value is received every second
                }
                time = DateTime.Now;

                foreach (int value in valueQueue2)
                {
                    DataPlot.Series["Node2"].Points.AddXY(time, value);
                    time = time.AddSeconds(1);
                }
                time = DateTime.Now;

                foreach (int value in valueQueue3)
                {
                    DataPlot.Series["Node3"].Points.AddXY(time, value);
                    time = time.AddSeconds(1);
                }
                time = DateTime.Now;

                foreach (int value in valueQueue4)
                {
                    DataPlot.Series["Node4"].Points.AddXY(time, value);
                    time = time.AddSeconds(1);
                }

                // Set the x-axis scrollbar position to show the last 8 points
                int position = DataPlot.Series["Node1"].Points.Count - 8;
                DataPlot.ChartAreas["ChartArea1"].AxisX.ScaleView.Position = position > 0 ? position : 0;
            }));
        }
        private void buttonActuator1_Click(object sender, EventArgs e)
        {
            try
            {
                if (isOn)
                {
                    serialPort1.WriteLine("$Off1"); // Cambio en el comando para apagar LED 32
                    Actuator1.Image = Properties.Resources.LED_R;
                    buttonActuator1.Text = "OFF";
                    buttonActuator1.BackColor = Color.Red;
                }
                else
                {
                    serialPort1.WriteLine("$On1"); // Cambio en el comando para encender LED 32
                    Actuator1.Image = Properties.Resources.LED_G;
                    buttonActuator1.Text = "ON";
                    buttonActuator1.BackColor = Color.Green;
                }
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }

            isOn = !isOn;
        }

        private void buttonActuator2_Click(object sender, EventArgs e)
        {
            try
            {
                if (isOn)
                {
                    serialPort1.WriteLine("$Off2"); // Cambio en el comando para apagar LED 33
                    Actuator2.Image = Properties.Resources.LED_R;
                    buttonActuator2.Text = "OFF";
                    buttonActuator2.BackColor = Color.Red;
                }
                else
                {
                    serialPort1.WriteLine("$On2"); // Cambio en el comando para encender LED 33
                    Actuator2.Image = Properties.Resources.LED_G;
                    buttonActuator2.Text = "ON";
                    buttonActuator2.BackColor = Color.Green;
                }
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
            }

            isOn = !isOn;
        }


    }
}
