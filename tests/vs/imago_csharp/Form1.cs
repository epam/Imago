using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace imago_csharp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        [DllImport("test.vs.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int recognize(IntPtr image, int width, int height,
                                                     IntPtr outputbuffer, int buf_size,
                                                     IntPtr warnings, IntPtr reserved);

        private void Form1_Load(object sender, EventArgs e)
        {            
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OpenFileDialog dlg = new OpenFileDialog();
            if (dlg.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                pictureBox1.Load(dlg.FileName);
            }
        }

        public static string recognize(Bitmap bitmap)
        {
            int width = bitmap.Width;
            int height = bitmap.Height;
            int image_size = width * height;

            byte[] image_data = new byte[image_size];

            for (int x = 0; x < width; x++)
                for (int y = 0; y < height; y++)
                    image_data[x + y * width] = (byte)((bitmap.GetPixel(x, y).R * 30 + bitmap.GetPixel(x, y).G * 59 + bitmap.GetPixel(x, y).B * 11) / 100);

            IntPtr image_buffer = Marshal.AllocHGlobal(image_size);
            Marshal.Copy(image_data, 0, image_buffer, image_size);

            int buffer_size = 65536;
            byte[] molfile_data = new byte[buffer_size];
            for (int i = 0; i < buffer_size; i++)
                molfile_data[i] = 0;

            IntPtr output_buffer = Marshal.AllocHGlobal(buffer_size);
            Marshal.Copy(molfile_data, 0, output_buffer, buffer_size);

            IntPtr warnings_buffer = Marshal.AllocHGlobal(4);

            int result = recognize(image_buffer, width, height, output_buffer, buffer_size, warnings_buffer, IntPtr.Zero);

            Marshal.Copy(output_buffer, molfile_data, 0, buffer_size);
            string molfile_string = System.Text.ASCIIEncoding.Default.GetString(molfile_data);

            Marshal.FreeHGlobal(output_buffer);
            Marshal.FreeHGlobal(image_buffer);
            Marshal.FreeHGlobal(warnings_buffer);

            return molfile_string;
        }

        private void button2_Click(object sender, EventArgs e)
        {
            MessageBox.Show(recognize(new Bitmap(pictureBox1.Image)));            
        }
    }
}
