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

        private void button2_Click(object sender, EventArgs e)
        {
            Bitmap bitmap = new Bitmap(pictureBox1.Image);

            int width = bitmap.Width;
            int height = bitmap.Height;
            int imagesize = width * height;
            
            byte[] imagedata = new byte[imagesize];

            for (int x = 0; x < width; x++)
            {
                for (int y = 0; y < height; y++)
                {
                    imagedata[x + y * width] = bitmap.GetPixel(x, y).B;
                }
            }

            IntPtr image = Marshal.AllocHGlobal(imagesize);
            Marshal.Copy(imagedata, 0, image, imagesize);

            int bufsize = 65536;
            byte[] data = new byte[bufsize];            
            IntPtr outputbuffer = Marshal.AllocHGlobal(bufsize);

            IntPtr warnings = Marshal.AllocHGlobal(4);

            int result = recognize(image, width, height, outputbuffer, bufsize, warnings, IntPtr.Zero);

            Marshal.Copy(outputbuffer, data, 0, bufsize);
            string molfile = System.Text.ASCIIEncoding.Default.GetString(data);
            MessageBox.Show("result: " + result.ToString() + "; output: " + molfile);

            Marshal.FreeHGlobal(outputbuffer);
            Marshal.FreeHGlobal(image);
            Marshal.FreeHGlobal(warnings);
        }
    }
}
