namespace GUI
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea1 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend1 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series1 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series2 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series3 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series4 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.groupBoxHeader = new System.Windows.Forms.GroupBox();
            this.Name4 = new System.Windows.Forms.Label();
            this.Name3 = new System.Windows.Forms.Label();
            this.pictureCHEC = new System.Windows.Forms.PictureBox();
            this.pictureUAM = new System.Windows.Forms.PictureBox();
            this.Name2 = new System.Windows.Forms.Label();
            this.Name1 = new System.Windows.Forms.Label();
            this.groupBoxCOMPort = new System.Windows.Forms.GroupBox();
            this.progressBarConnection = new System.Windows.Forms.ProgressBar();
            this.buttonClose = new System.Windows.Forms.Button();
            this.buttonOpen = new System.Windows.Forms.Button();
            this.comboBoxBaudRate = new System.Windows.Forms.ComboBox();
            this.comboBoxPort = new System.Windows.Forms.ComboBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.groupBoxStatus = new System.Windows.Forms.GroupBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBoxN4 = new System.Windows.Forms.PictureBox();
            this.pictureBoxN3 = new System.Windows.Forms.PictureBox();
            this.pictureBoxN2 = new System.Windows.Forms.PictureBox();
            this.pictureBoxN1 = new System.Windows.Forms.PictureBox();
            this.groupBoxData = new System.Windows.Forms.GroupBox();
            this.DataPlot = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.groupBoxActuators = new System.Windows.Forms.GroupBox();
            this.pictureActuator2 = new System.Windows.Forms.PictureBox();
            this.pictureActuator1 = new System.Windows.Forms.PictureBox();
            this.Name5 = new System.Windows.Forms.Label();
            this.Actuator2 = new System.Windows.Forms.PictureBox();
            this.Actuator1 = new System.Windows.Forms.PictureBox();
            this.buttonActuator2 = new System.Windows.Forms.Button();
            this.buttonActuator1 = new System.Windows.Forms.Button();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.groupBoxHeader.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureCHEC)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureUAM)).BeginInit();
            this.groupBoxCOMPort.SuspendLayout();
            this.groupBoxStatus.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxN4)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxN3)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxN2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxN1)).BeginInit();
            this.groupBoxData.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.DataPlot)).BeginInit();
            this.groupBoxActuators.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureActuator2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureActuator1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Actuator2)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.Actuator1)).BeginInit();
            this.SuspendLayout();
            // 
            // groupBoxHeader
            // 
            this.groupBoxHeader.Controls.Add(this.Name4);
            this.groupBoxHeader.Controls.Add(this.Name3);
            this.groupBoxHeader.Controls.Add(this.pictureCHEC);
            this.groupBoxHeader.Controls.Add(this.pictureUAM);
            this.groupBoxHeader.Controls.Add(this.Name2);
            this.groupBoxHeader.Controls.Add(this.Name1);
            this.groupBoxHeader.Controls.Add(this.groupBoxCOMPort);
            this.groupBoxHeader.Location = new System.Drawing.Point(20, 15);
            this.groupBoxHeader.Name = "groupBoxHeader";
            this.groupBoxHeader.Size = new System.Drawing.Size(269, 569);
            this.groupBoxHeader.TabIndex = 0;
            this.groupBoxHeader.TabStop = false;
            // 
            // Name4
            // 
            this.Name4.AutoSize = true;
            this.Name4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name4.Location = new System.Drawing.Point(84, 287);
            this.Name4.Name = "Name4";
            this.Name4.Size = new System.Drawing.Size(104, 25);
            this.Name4.TabIndex = 7;
            this.Name4.Text = "eléctricas";
            // 
            // Name3
            // 
            this.Name3.AutoSize = true;
            this.Name3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name3.Location = new System.Drawing.Point(56, 253);
            this.Name3.Name = "Name3";
            this.Name3.Size = new System.Drawing.Size(151, 25);
            this.Name3.TabIndex = 6;
            this.Name3.Text = "subestaciones";
            // 
            // pictureCHEC
            // 
            this.pictureCHEC.Image = ((System.Drawing.Image)(resources.GetObject("pictureCHEC.Image")));
            this.pictureCHEC.Location = new System.Drawing.Point(147, 43);
            this.pictureCHEC.Name = "pictureCHEC";
            this.pictureCHEC.Size = new System.Drawing.Size(113, 72);
            this.pictureCHEC.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureCHEC.TabIndex = 5;
            this.pictureCHEC.TabStop = false;
            // 
            // pictureUAM
            // 
            this.pictureUAM.Image = ((System.Drawing.Image)(resources.GetObject("pictureUAM.Image")));
            this.pictureUAM.Location = new System.Drawing.Point(6, 43);
            this.pictureUAM.Name = "pictureUAM";
            this.pictureUAM.Size = new System.Drawing.Size(142, 72);
            this.pictureUAM.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureUAM.TabIndex = 4;
            this.pictureUAM.TabStop = false;
            // 
            // Name2
            // 
            this.Name2.AutoSize = true;
            this.Name2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name2.Location = new System.Drawing.Point(56, 218);
            this.Name2.Name = "Name2";
            this.Name2.Size = new System.Drawing.Size(132, 25);
            this.Name2.TabIndex = 3;
            this.Name2.Text = " de fauna en";
            // 
            // Name1
            // 
            this.Name1.AutoSize = true;
            this.Name1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name1.Location = new System.Drawing.Point(38, 182);
            this.Name1.Name = "Name1";
            this.Name1.Size = new System.Drawing.Size(187, 25);
            this.Name1.TabIndex = 2;
            this.Name1.Text = "IoT para el control";
            // 
            // groupBoxCOMPort
            // 
            this.groupBoxCOMPort.Controls.Add(this.progressBarConnection);
            this.groupBoxCOMPort.Controls.Add(this.buttonClose);
            this.groupBoxCOMPort.Controls.Add(this.buttonOpen);
            this.groupBoxCOMPort.Controls.Add(this.comboBoxBaudRate);
            this.groupBoxCOMPort.Controls.Add(this.comboBoxPort);
            this.groupBoxCOMPort.Controls.Add(this.label6);
            this.groupBoxCOMPort.Controls.Add(this.label5);
            this.groupBoxCOMPort.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBoxCOMPort.Location = new System.Drawing.Point(10, 363);
            this.groupBoxCOMPort.Name = "groupBoxCOMPort";
            this.groupBoxCOMPort.Size = new System.Drawing.Size(250, 200);
            this.groupBoxCOMPort.TabIndex = 1;
            this.groupBoxCOMPort.TabStop = false;
            // 
            // progressBarConnection
            // 
            this.progressBarConnection.Location = new System.Drawing.Point(7, 173);
            this.progressBarConnection.Name = "progressBarConnection";
            this.progressBarConnection.Size = new System.Drawing.Size(235, 12);
            this.progressBarConnection.TabIndex = 6;
            // 
            // buttonClose
            // 
            this.buttonClose.Location = new System.Drawing.Point(140, 125);
            this.buttonClose.Name = "buttonClose";
            this.buttonClose.Size = new System.Drawing.Size(90, 35);
            this.buttonClose.TabIndex = 5;
            this.buttonClose.Text = "CLOSE";
            this.buttonClose.UseVisualStyleBackColor = true;
            this.buttonClose.Click += new System.EventHandler(this.buttonClose_Click);
            // 
            // buttonOpen
            // 
            this.buttonOpen.Location = new System.Drawing.Point(20, 125);
            this.buttonOpen.Name = "buttonOpen";
            this.buttonOpen.Size = new System.Drawing.Size(90, 35);
            this.buttonOpen.TabIndex = 4;
            this.buttonOpen.Text = "OPEN";
            this.buttonOpen.UseVisualStyleBackColor = true;
            this.buttonOpen.Click += new System.EventHandler(this.buttonOpen_Click);
            // 
            // comboBoxBaudRate
            // 
            this.comboBoxBaudRate.FormattingEnabled = true;
            this.comboBoxBaudRate.Items.AddRange(new object[] {
            "3600",
            "7200",
            "9600",
            "14400",
            "19200",
            "28800",
            "38400",
            "57600",
            "115200"});
            this.comboBoxBaudRate.Location = new System.Drawing.Point(126, 77);
            this.comboBoxBaudRate.Name = "comboBoxBaudRate";
            this.comboBoxBaudRate.Size = new System.Drawing.Size(118, 28);
            this.comboBoxBaudRate.TabIndex = 3;
            // 
            // comboBoxPort
            // 
            this.comboBoxPort.FormattingEnabled = true;
            this.comboBoxPort.Location = new System.Drawing.Point(126, 33);
            this.comboBoxPort.Name = "comboBoxPort";
            this.comboBoxPort.Size = new System.Drawing.Size(118, 28);
            this.comboBoxPort.TabIndex = 2;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(6, 81);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(92, 18);
            this.label6.TabIndex = 1;
            this.label6.Text = "BAUD RATE";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(6, 37);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(90, 18);
            this.label5.TabIndex = 0;
            this.label5.Text = "COM PORT";
            // 
            // groupBoxStatus
            // 
            this.groupBoxStatus.Controls.Add(this.label4);
            this.groupBoxStatus.Controls.Add(this.label3);
            this.groupBoxStatus.Controls.Add(this.label2);
            this.groupBoxStatus.Controls.Add(this.label1);
            this.groupBoxStatus.Controls.Add(this.pictureBoxN4);
            this.groupBoxStatus.Controls.Add(this.pictureBoxN3);
            this.groupBoxStatus.Controls.Add(this.pictureBoxN2);
            this.groupBoxStatus.Controls.Add(this.pictureBoxN1);
            this.groupBoxStatus.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBoxStatus.Location = new System.Drawing.Point(295, 15);
            this.groupBoxStatus.Name = "groupBoxStatus";
            this.groupBoxStatus.Size = new System.Drawing.Size(750, 105);
            this.groupBoxStatus.TabIndex = 2;
            this.groupBoxStatus.TabStop = false;
            this.groupBoxStatus.Text = "STATUS";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(610, 45);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(94, 25);
            this.label4.TabIndex = 10;
            this.label4.Text = "NODO 4";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(430, 45);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(94, 25);
            this.label3.TabIndex = 9;
            this.label3.Text = "NODO 3";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(250, 45);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(94, 25);
            this.label2.TabIndex = 8;
            this.label2.Text = "NODO 2";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(70, 45);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(94, 25);
            this.label1.TabIndex = 7;
            this.label1.Text = "NODO 1";
            // 
            // pictureBoxN4
            // 
            this.pictureBoxN4.Image = global::GUI.Properties.Resources.LED_R;
            this.pictureBoxN4.Location = new System.Drawing.Point(560, 25);
            this.pictureBoxN4.Name = "pictureBoxN4";
            this.pictureBoxN4.Size = new System.Drawing.Size(40, 59);
            this.pictureBoxN4.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBoxN4.TabIndex = 4;
            this.pictureBoxN4.TabStop = false;
            // 
            // pictureBoxN3
            // 
            this.pictureBoxN3.Image = global::GUI.Properties.Resources.LED_R;
            this.pictureBoxN3.Location = new System.Drawing.Point(380, 25);
            this.pictureBoxN3.Name = "pictureBoxN3";
            this.pictureBoxN3.Size = new System.Drawing.Size(40, 59);
            this.pictureBoxN3.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBoxN3.TabIndex = 5;
            this.pictureBoxN3.TabStop = false;
            // 
            // pictureBoxN2
            // 
            this.pictureBoxN2.Image = global::GUI.Properties.Resources.LED_R;
            this.pictureBoxN2.Location = new System.Drawing.Point(200, 25);
            this.pictureBoxN2.Name = "pictureBoxN2";
            this.pictureBoxN2.Size = new System.Drawing.Size(40, 59);
            this.pictureBoxN2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBoxN2.TabIndex = 6;
            this.pictureBoxN2.TabStop = false;
            // 
            // pictureBoxN1
            // 
            this.pictureBoxN1.Image = global::GUI.Properties.Resources.LED_R;
            this.pictureBoxN1.Location = new System.Drawing.Point(20, 25);
            this.pictureBoxN1.Name = "pictureBoxN1";
            this.pictureBoxN1.Size = new System.Drawing.Size(40, 59);
            this.pictureBoxN1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBoxN1.TabIndex = 0;
            this.pictureBoxN1.TabStop = false;
            // 
            // groupBoxData
            // 
            this.groupBoxData.Controls.Add(this.DataPlot);
            this.groupBoxData.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBoxData.Location = new System.Drawing.Point(295, 126);
            this.groupBoxData.Name = "groupBoxData";
            this.groupBoxData.Size = new System.Drawing.Size(746, 458);
            this.groupBoxData.TabIndex = 3;
            this.groupBoxData.TabStop = false;
            this.groupBoxData.Text = "DATA";
            // 
            // DataPlot
            // 
            chartArea1.Name = "ChartArea1";
            this.DataPlot.ChartAreas.Add(chartArea1);
            legend1.Name = "Legend1";
            this.DataPlot.Legends.Add(legend1);
            this.DataPlot.Location = new System.Drawing.Point(12, 23);
            this.DataPlot.Name = "DataPlot";
            series1.BorderWidth = 3;
            series1.ChartArea = "ChartArea1";
            series1.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series1.Color = System.Drawing.Color.Yellow;
            series1.Legend = "Legend1";
            series1.Name = "Node1";
            series1.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            series1.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
            series2.BorderWidth = 3;
            series2.ChartArea = "ChartArea1";
            series2.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series2.Color = System.Drawing.Color.Blue;
            series2.Legend = "Legend1";
            series2.Name = "Node2";
            series2.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            series2.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
            series3.BorderWidth = 3;
            series3.ChartArea = "ChartArea1";
            series3.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series3.Color = System.Drawing.Color.Lime;
            series3.Legend = "Legend1";
            series3.Name = "Node3";
            series3.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            series3.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
            series4.BorderWidth = 3;
            series4.ChartArea = "ChartArea1";
            series4.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Spline;
            series4.Color = System.Drawing.Color.Red;
            series4.Legend = "Legend1";
            series4.Name = "Node4";
            series4.XValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Time;
            series4.YValueType = System.Windows.Forms.DataVisualization.Charting.ChartValueType.Double;
            this.DataPlot.Series.Add(series1);
            this.DataPlot.Series.Add(series2);
            this.DataPlot.Series.Add(series3);
            this.DataPlot.Series.Add(series4);
            this.DataPlot.Size = new System.Drawing.Size(723, 425);
            this.DataPlot.TabIndex = 0;
            this.DataPlot.Text = "chart1";
            this.DataPlot.Click += new System.EventHandler(this.DataPlot_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // groupBoxActuators
            // 
            this.groupBoxActuators.Controls.Add(this.label8);
            this.groupBoxActuators.Controls.Add(this.label7);
            this.groupBoxActuators.Controls.Add(this.pictureActuator2);
            this.groupBoxActuators.Controls.Add(this.pictureActuator1);
            this.groupBoxActuators.Controls.Add(this.Name5);
            this.groupBoxActuators.Controls.Add(this.Actuator2);
            this.groupBoxActuators.Controls.Add(this.Actuator1);
            this.groupBoxActuators.Controls.Add(this.buttonActuator2);
            this.groupBoxActuators.Controls.Add(this.buttonActuator1);
            this.groupBoxActuators.Location = new System.Drawing.Point(1051, 15);
            this.groupBoxActuators.Name = "groupBoxActuators";
            this.groupBoxActuators.Size = new System.Drawing.Size(269, 569);
            this.groupBoxActuators.TabIndex = 4;
            this.groupBoxActuators.TabStop = false;
            // 
            // pictureActuator2
            // 
            this.pictureActuator2.Image = ((System.Drawing.Image)(resources.GetObject("pictureActuator2.Image")));
            this.pictureActuator2.Location = new System.Drawing.Point(151, 297);
            this.pictureActuator2.Name = "pictureActuator2";
            this.pictureActuator2.Size = new System.Drawing.Size(74, 72);
            this.pictureActuator2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureActuator2.TabIndex = 10;
            this.pictureActuator2.TabStop = false;
            // 
            // pictureActuator1
            // 
            this.pictureActuator1.Image = ((System.Drawing.Image)(resources.GetObject("pictureActuator1.Image")));
            this.pictureActuator1.Location = new System.Drawing.Point(138, 128);
            this.pictureActuator1.Name = "pictureActuator1";
            this.pictureActuator1.Size = new System.Drawing.Size(100, 91);
            this.pictureActuator1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureActuator1.TabIndex = 9;
            this.pictureActuator1.TabStop = false;
            // 
            // Name5
            // 
            this.Name5.AutoSize = true;
            this.Name5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Name5.Location = new System.Drawing.Point(8, 43);
            this.Name5.Name = "Name5";
            this.Name5.Size = new System.Drawing.Size(228, 25);
            this.Name5.TabIndex = 8;
            this.Name5.Text = "Control de Actuadores";
            // 
            // Actuator2
            // 
            this.Actuator2.Image = global::GUI.Properties.Resources.LED_R;
            this.Actuator2.Location = new System.Drawing.Point(71, 283);
            this.Actuator2.Name = "Actuator2";
            this.Actuator2.Size = new System.Drawing.Size(40, 59);
            this.Actuator2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Actuator2.TabIndex = 5;
            this.Actuator2.TabStop = false;
            // 
            // Actuator1
            // 
            this.Actuator1.Image = global::GUI.Properties.Resources.LED_R;
            this.Actuator1.Location = new System.Drawing.Point(71, 128);
            this.Actuator1.Name = "Actuator1";
            this.Actuator1.Size = new System.Drawing.Size(40, 59);
            this.Actuator1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.Actuator1.TabIndex = 5;
            this.Actuator1.TabStop = false;
            // 
            // buttonActuator2
            // 
            this.buttonActuator2.Location = new System.Drawing.Point(42, 348);
            this.buttonActuator2.Name = "buttonActuator2";
            this.buttonActuator2.Size = new System.Drawing.Size(90, 35);
            this.buttonActuator2.TabIndex = 5;
            this.buttonActuator2.Text = "OFF";
            this.buttonActuator2.UseVisualStyleBackColor = true;
            this.buttonActuator2.Click += new System.EventHandler(this.buttonActuator2_Click);
            // 
            // buttonActuator1
            // 
            this.buttonActuator1.Location = new System.Drawing.Point(42, 193);
            this.buttonActuator1.Name = "buttonActuator1";
            this.buttonActuator1.Size = new System.Drawing.Size(90, 35);
            this.buttonActuator1.TabIndex = 5;
            this.buttonActuator1.Text = "OFF";
            this.buttonActuator1.UseVisualStyleBackColor = true;
            this.buttonActuator1.Click += new System.EventHandler(this.buttonActuator1_Click);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(32, 95);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(202, 20);
            this.label7.TabIndex = 11;
            this.label7.Text = "Disuasor GREEN-LASÉR";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Italic, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(32, 257);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(193, 20);
            this.label8.TabIndex = 12;
            this.label8.Text = "Disuador NEBU-SMART";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.ButtonHighlight;
            this.ClientSize = new System.Drawing.Size(1331, 613);
            this.Controls.Add(this.groupBoxActuators);
            this.Controls.Add(this.groupBoxData);
            this.Controls.Add(this.groupBoxStatus);
            this.Controls.Add(this.groupBoxHeader);
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Form1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.MouseEnter += new System.EventHandler(this.Form1_MouseEnter);
            this.MouseLeave += new System.EventHandler(this.Form1_MouseLeave);
            this.groupBoxHeader.ResumeLayout(false);
            this.groupBoxHeader.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureCHEC)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureUAM)).EndInit();
            this.groupBoxCOMPort.ResumeLayout(false);
            this.groupBoxCOMPort.PerformLayout();
            this.groupBoxStatus.ResumeLayout(false);
            this.groupBoxStatus.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxN4)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxN3)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxN2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxN1)).EndInit();
            this.groupBoxData.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.DataPlot)).EndInit();
            this.groupBoxActuators.ResumeLayout(false);
            this.groupBoxActuators.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureActuator2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureActuator1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Actuator2)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.Actuator1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxHeader;
        private System.Windows.Forms.GroupBox groupBoxCOMPort;
        private System.Windows.Forms.GroupBox groupBoxStatus;
        private System.Windows.Forms.GroupBox groupBoxData;
        private System.Windows.Forms.DataVisualization.Charting.Chart DataPlot;
        private System.Windows.Forms.PictureBox pictureCHEC;
        private System.Windows.Forms.PictureBox pictureUAM;
        private System.Windows.Forms.Label Name2;
        private System.Windows.Forms.Label Name1;
        private System.Windows.Forms.PictureBox pictureBoxN1;
        private System.Windows.Forms.PictureBox pictureBoxN4;
        private System.Windows.Forms.PictureBox pictureBoxN3;
        private System.Windows.Forms.PictureBox pictureBoxN2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label Name3;
        private System.Windows.Forms.Label Name4;
        private System.Windows.Forms.ComboBox comboBoxPort;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ComboBox comboBoxBaudRate;
        private System.Windows.Forms.Button buttonClose;
        private System.Windows.Forms.Button buttonOpen;
        private System.Windows.Forms.ProgressBar progressBarConnection;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.GroupBox groupBoxActuators;
        private System.Windows.Forms.PictureBox Actuator2;
        private System.Windows.Forms.PictureBox Actuator1;
        private System.Windows.Forms.Button buttonActuator2;
        private System.Windows.Forms.Button buttonActuator1;
        private System.Windows.Forms.Label Name5;
        private System.Windows.Forms.PictureBox pictureActuator2;
        private System.Windows.Forms.PictureBox pictureActuator1;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
    }
}

