// Decompiled with JetBrains decompiler
// Type: AliceInCeptionland.CheshireCat
// Assembly: AliceInCeptionland, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 01DC5997-384E-427D-A025-8486AE92950A
// Assembly location: D:\corctf\aliceinception\AliceInCeptionland.exe

using AliceInCeptionland.Properties;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Windows.Forms;

namespace AliceInCeptionland
{
  public class CheshireCat : Form
  {
    private int ticks;
    private IContainer components;
    private PictureBox imgCat;
    private PictureBox imgExplosion;
    private PictureBox imgCatLaser;
    private Timer timer1;
    private Label label1;
    private Button button1;
    private TextBox textBox1;

    public string Secret { get; private set; } = string.Empty;

    public CheshireCat() => this.InitializeComponent();

    private void button1_Click(object sender, EventArgs e)
    {
      string str = WhiteRabbit.Transform("41!ce1337");
      char[] array = WhiteRabbit.Transform(this.textBox1.Text).Reverse<char>().ToArray<char>();
      for (int index = 0; index < array.Length; ++index)
        array[index] ^= str[index % str.Length];
      if (!string.Join<char>("", ((IEnumerable<char>) array).Reverse<char>()).Equals("oI!&}IusoKs ?Ytr"))
        return;

        //\xDE\xAD\xBE\xEF
      this.Secret = this.textBox1.Text;
      this.label1.Visible = false;
      this.textBox1.Visible = false;
      this.button1.Visible = false;
      this.timer1.Start();
    }

    private void timer1_Tick(object sender, EventArgs e)
    {
      ++this.ticks;
      if (this.ticks < 10)
      {
        Point location = this.imgCat.Location;
        if (this.ticks % 2 == 1)
          this.imgCat.Location = new Point(location.X, location.Y - 5);
        else
          this.imgCat.Location = new Point(location.X, location.Y + 5);
      }
      else if (this.ticks == 10)
      {
        this.imgCat.Visible = false;
        this.imgCatLaser.Visible = true;
      }
      else if (this.ticks == 20)
      {
        this.imgCatLaser.Visible = false;
        this.imgExplosion.Visible = true;
      }
      else
      {
        if (this.ticks < 30)
          return;
        this.timer1.Stop();
        this.DialogResult = DialogResult.OK;
        this.Close();
      }
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      this.components = (IContainer) new Container();
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (CheshireCat));
      this.imgCat = new PictureBox();
      this.imgExplosion = new PictureBox();
      this.imgCatLaser = new PictureBox();
      this.timer1 = new Timer(this.components);
      this.label1 = new Label();
      this.button1 = new Button();
      this.textBox1 = new TextBox();
      ((ISupportInitialize) this.imgCat).BeginInit();
      ((ISupportInitialize) this.imgExplosion).BeginInit();
      ((ISupportInitialize) this.imgCatLaser).BeginInit();
      this.SuspendLayout();
      this.imgCat.BackColor = Color.Transparent;
      this.imgCat.Image = (Image) Resources.madcat2;
      this.imgCat.Location = new Point(175, 0);
      this.imgCat.Name = "imgCat";
      this.imgCat.Size = new Size(380, 173);
      this.imgCat.TabIndex = 1;
      this.imgCat.TabStop = false;
      this.imgExplosion.BackColor = Color.Transparent;
      this.imgExplosion.Image = (Image) Resources.explosion;
      this.imgExplosion.Location = new Point(322, 0);
      this.imgExplosion.Name = "imgExplosion";
      this.imgExplosion.Size = new Size(233, 173);
      this.imgExplosion.TabIndex = 2;
      this.imgExplosion.TabStop = false;
      this.imgExplosion.Visible = false;
      this.imgCatLaser.BackColor = Color.Transparent;
      this.imgCatLaser.Image = (Image) Resources.madcat3;
      this.imgCatLaser.Location = new Point(175, 0);
      this.imgCatLaser.Name = "imgCatLaser";
      this.imgCatLaser.Size = new Size(380, 173);
      this.imgCatLaser.TabIndex = 6;
      this.imgCatLaser.TabStop = false;
      this.timer1.Tick += new EventHandler(this.timer1_Tick);
      this.label1.AutoSize = true;
      this.label1.BackColor = Color.Transparent;
      this.label1.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label1.Location = new Point(28, 280);
      this.label1.Name = "label1";
      this.label1.Size = new Size(486, 32);
      this.label1.TabIndex = 13;
      this.label1.Text = "Oh no! The evil cat, Count Scratchington, has maliciously entered Alice's dreams!\r\nQuickly, enter the activation password to arm the dream self-defense mechanism!";
      this.button1.Location = new Point(399, 316);
      this.button1.Name = "button1";
      this.button1.Size = new Size(129, 29);
      this.button1.TabIndex = 14;
      this.button1.Text = "REEEEEEEEE";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.textBox1.Location = new Point(31, 321);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(362, 20);
      this.textBox1.TabIndex = 12;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackgroundImage = (Image) Resources.alice;
      this.ClientSize = new Size(555, 370);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.imgExplosion);
      this.Controls.Add((Control) this.imgCat);
      this.Controls.Add((Control) this.imgCatLaser);
      this.DoubleBuffered = true;
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (CheshireCat);
      this.Text = "Alice In Ceptionland - The Cheshire Cat";
      ((ISupportInitialize) this.imgCat).EndInit();
      ((ISupportInitialize) this.imgExplosion).EndInit();
      ((ISupportInitialize) this.imgCatLaser).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
