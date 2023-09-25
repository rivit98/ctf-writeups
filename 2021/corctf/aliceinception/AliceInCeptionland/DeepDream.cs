// Decompiled with JetBrains decompiler
// Type: AliceInCeptionland.DeepDream
// Assembly: AliceInCeptionland, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 01DC5997-384E-427D-A025-8486AE92950A
// Assembly location: D:\corctf\aliceinception\AliceInCeptionland.exe

using AliceInCeptionland.Properties;
using System;
using System.ComponentModel;
using System.Drawing;
using System.Reflection;
using System.Text;
using System.Windows.Forms;

namespace AliceInCeptionland
{
  public class DeepDream : Form
  {
    private IContainer components;
    private Label label1;
    private Button button1;
    private TextBox textBox1;
    private Label label2;
    private Button button2;

    private Assembly Dream { get; }

    public DeepDream(Assembly dream)
    {
      this.InitializeComponent();
      this.Dream = dream;
    }

    private void button1_Click(object sender, EventArgs e)
    {
      if (!((string) this.Dream.GetType("AliceInCeptiondream.Dream").GetMethod("Encode").Invoke((object) null, new object[1]
      {
        (object) this.textBox1.Text
      })).Equals("3c3cf1df89fe832aefcc22fc82017cd57bef01df54235e21414122d78a9d88cfef3cf10c829ee32ae4ef01dfa1951cd51b7b22fc82433ef7ef418cdf8a9d802101ef64f9a495268fef18d52882324f217b1bd64b82017cd57bef01df255288f7593922712c958029e7efccdf081f8808a6efd5287595f821482822f6cb95f821cceff4695495268fefe72ad7821a67ae0060ad"))
      {
        int num = (int) MessageBox.Show((IWin32Window) this, "If you were to chant these words of stupidity,\nI'd imagine we would never see Alice again...\nTry another chant... Something has to work!", "Probably you are 1000 kilogram in basement.");
      }
      else
      {
        this.label1.Visible = false;
        this.button1.Visible = false;
        this.textBox1.Visible = false;
        this.label2.Visible = true;
        this.button2.Visible = true;
      }
    }

    private void button2_Click(object sender, EventArgs e)
    {
      byte[] numArray = new byte[176]
      {
        (byte) 152,
        (byte) 52,
        (byte) 210,
        (byte) 108,
        (byte) 209,
        (byte) 182,
        (byte) 69,
        (byte) 150,
        (byte) 153,
        (byte) 40,
        (byte) 64,
        (byte) 133,
        (byte) 135,
        (byte) 200,
        (byte) 181,
        (byte) 146,
        (byte) 187,
        (byte) 125,
        (byte) 217,
        (byte) 241,
        (byte) 62,
        (byte) 251,
        (byte) 72,
        (byte) 128,
        (byte) 232,
        (byte) 134,
        (byte) 143,
        (byte) 221,
        (byte) 236,
        (byte) 15,
        (byte) 120,
        (byte) 21,
        (byte) 213,
        (byte) 43,
        (byte) 99,
        (byte) 72,
        (byte) 163,
        (byte) 243,
        (byte) 21,
        (byte) 217,
        (byte) 41,
        (byte) 81,
        (byte) 246,
        (byte) 174,
        (byte) 229,
        (byte) 49,
        (byte) 10,
        (byte) 200,
        (byte) 70,
        (byte) 138,
        (byte) 103,
        (byte) 174,
        (byte) 160,
        (byte) 80,
        (byte) 66,
        (byte) 99,
        (byte) 250,
        (byte) 166,
        (byte) 73,
        (byte) 217,
        (byte) 220,
        (byte) 94,
        (byte) 146,
        (byte) 153,
        (byte) 150,
        (byte) 43,
        (byte) 120,
        (byte) 46,
        (byte) 150,
        (byte) 203,
        (byte) 20,
        (byte) 198,
        (byte) 211,
        (byte) 89,
        (byte) 35,
        (byte) 134,
        (byte) 89,
        (byte) 132,
        (byte) 190,
        (byte) 205,
        (byte) 141,
        (byte) 237,
        (byte) 201,
        (byte) 119,
        (byte) 178,
        (byte) 47,
        (byte) 211,
        (byte) 182,
        (byte) 156,
        (byte) 56,
        (byte) 17,
        (byte) 111,
        (byte) 146,
        (byte) 167,
        (byte) 228,
        (byte) 133,
        (byte) 51,
        (byte) 187,
        (byte) 48,
        (byte) 213,
        (byte) 206,
        (byte) 208,
        (byte) 254,
        (byte) 71,
        (byte) 205,
        (byte) 76,
        (byte) 36,
        (byte) 119,
        (byte) 32,
        (byte) 204,
        (byte) 50,
        (byte) 217,
        (byte) 167,
        (byte) 42,
        (byte) 224,
        (byte) 80,
        (byte) 91,
        (byte) 102,
        (byte) 225,
        (byte) 152,
        (byte) 14,
        (byte) 94,
        (byte) 73,
        (byte) 60,
        (byte) 145,
        (byte) 152,
        (byte) 240,
        (byte) 188,
        (byte) 182,
        (byte) 190,
        (byte) 182,
        (byte) 166,
        (byte) 98,
        (byte) 5,
        (byte) 234,
        (byte) 116,
        (byte) 229,
        (byte) 27,
        (byte) 90,
        byte.MaxValue,
        (byte) 109,
        (byte) 15,
        (byte) 219,
        (byte) 83,
        (byte) 34,
        (byte) 15,
        (byte) 22,
        (byte) 147,
        (byte) 170,
        (byte) 234,
        (byte) 184,
        (byte) 109,
        (byte) 28,
        (byte) 1,
        (byte) 3,
        (byte) 178,
        (byte) 98,
        (byte) 31,
        (byte) 49,
        (byte) 250,
        (byte) 163,
        (byte) 196,
        (byte) 139,
        (byte) 204,
        (byte) 177,
        (byte) 95,
        (byte) 239,
        (byte) 172,
        (byte) 138,
        (byte) 50,
        (byte) 189,
        (byte) 238,
        (byte) 57,
        (byte) 177,
        (byte) 110,
        (byte) 206
      };
      int num = (int) MessageBox.Show((IWin32Window) this, Encoding.UTF8.GetString((byte[]) this.Dream.GetType("AliceInCeptiondream.Dream").GetMethod("Decrypt").Invoke((object) null, new object[2]
      {
        (object) numArray,
        (object) this.textBox1.Text
      })), "Gommba is an idiot... Who is skilled at some things.");
      this.Close();
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (DeepDream));
      this.label1 = new Label();
      this.button1 = new Button();
      this.textBox1 = new TextBox();
      this.label2 = new Label();
      this.button2 = new Button();
      this.SuspendLayout();
      this.label1.AutoSize = true;
      this.label1.BackColor = Color.Transparent;
      this.label1.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label1.ForeColor = SystemColors.Control;
      this.label1.Location = new Point(373, 151);
      this.label1.Name = "label1";
      this.label1.Size = new Size(219, 240);
      this.label1.TabIndex = 0;
      this.label1.Text = componentResourceManager.GetString("label1.Text");
      this.button1.Location = new Point(372, 428);
      this.button1.Name = "button1";
      this.button1.Size = new Size(220, 40);
      this.button1.TabIndex = 1;
      this.button1.Text = "Chant Away!";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.textBox1.Location = new Point(372, 402);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(220, 20);
      this.textBox1.TabIndex = 2;
      this.label2.AutoSize = true;
      this.label2.BackColor = Color.Transparent;
      this.label2.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label2.ForeColor = SystemColors.Control;
      this.label2.Location = new Point(373, 151);
      this.label2.Name = "label2";
      this.label2.Size = new Size(231, 288);
      this.label2.TabIndex = 3;
      this.label2.Text = componentResourceManager.GetString("label2.Text");
      this.label2.Visible = false;
      this.button2.Location = new Point(372, 448);
      this.button2.Name = "button2";
      this.button2.Size = new Size(220, 40);
      this.button2.TabIndex = 4;
      this.button2.Text = "Follow The White Rabbit (and Alice)!";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Visible = false;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackgroundImage = (Image) Resources.alice1;
      this.ClientSize = new Size(640, 600);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.label2);
      this.DoubleBuffered = true;
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (DeepDream);
      this.Text = "Alice In Ceptionland";
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
