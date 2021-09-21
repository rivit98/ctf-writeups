// Decompiled with JetBrains decompiler
// Type: AliceInCeptionland.BaseGame
// Assembly: AliceInCeptionland, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 01DC5997-384E-427D-A025-8486AE92950A
// Assembly location: D:\corctf\aliceinception\AliceInCeptionland.exe

using AliceInCeptionland.Properties;
using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Media;
using System.Windows.Forms;

namespace AliceInCeptionland
{
  public class BaseGame : Form
  {
    private IContainer components;
    private PictureBox imgFirst;
    private PictureBox imgSecond;
    private PictureBox imgActor;

    public string Foo { get; private set; } = string.Empty;

    public string Bar { get; private set; } = string.Empty;

    public BaseGame() => this.InitializeComponent();

    private void BaseGame_Load(object sender, EventArgs e) => new SoundPlayer((Stream) Resources.Dash_Runner).PlayLooping();

    private void BaseGame_KeyDown(object sender, KeyEventArgs e)
    {
      Point location = this.imgActor.Location;
      if (e.KeyCode == Keys.Left)
        location.X = location.X < 60 ? 0 : location.X - 60;
      else if (e.KeyCode == Keys.Up)
        location.Y = location.Y < 60 ? 0 : location.Y - 60;
      else if (e.KeyCode == Keys.Right)
        location.X = location.X >= this.Size.Width - 120 ? location.X : location.X + 60;
      else if (e.KeyCode == Keys.Down)
        location.Y = location.Y >= this.Size.Height - 150 ? location.Y : location.Y + 60;
      if (location == this.imgFirst.Location && this.imgFirst.Visible)
      {
        this.Visible = false;
        CheshireCat cheshireCat = new CheshireCat();
        if (cheshireCat.ShowDialog((IWin32Window) this) != DialogResult.OK)
        {
          this.Close();
          return;
        }
        this.Foo = cheshireCat.Secret;
        this.imgFirst.Visible = false;
        this.Visible = true;
      }
      else if (location == this.imgSecond.Location)
      {
        if (this.imgFirst.Visible)
        {
          location = this.imgActor.Location;
        }
        else
        {
          this.Visible = false;
          Caterpillar caterpillar = new Caterpillar();
          if (caterpillar.ShowDialog((IWin32Window) this) != DialogResult.OK)
          {
            this.Close();
            return;
          }
          this.Bar = caterpillar.Secret;
          this.Visible = true;
          this.Close();
        }
      }
      this.imgActor.Location = location;
    }

    protected override void Dispose(bool disposing)
    {
      if (disposing && this.components != null)
        this.components.Dispose();
      base.Dispose(disposing);
    }

    private void InitializeComponent()
    {
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (BaseGame));
      this.imgFirst = new PictureBox();
      this.imgSecond = new PictureBox();
      this.imgActor = new PictureBox();
      ((ISupportInitialize) this.imgFirst).BeginInit();
      ((ISupportInitialize) this.imgSecond).BeginInit();
      ((ISupportInitialize) this.imgActor).BeginInit();
      this.SuspendLayout();
      this.imgFirst.BackColor = Color.Transparent;
      this.imgFirst.Image = (Image) Resources.question1;
      this.imgFirst.Location = new Point(360, 120);
      this.imgFirst.Name = "imgFirst";
      this.imgFirst.Size = new Size(60, 60);
      this.imgFirst.TabIndex = 0;
      this.imgFirst.TabStop = false;
      this.imgSecond.BackColor = Color.Transparent;
      this.imgSecond.Image = (Image) Resources.question2;
      this.imgSecond.Location = new Point(840, 540);
      this.imgSecond.Name = "imgSecond";
      this.imgSecond.Size = new Size(60, 60);
      this.imgSecond.TabIndex = 1;
      this.imgSecond.TabStop = false;
      this.imgActor.BackColor = Color.Transparent;
      this.imgActor.Image = (Image) Resources.actor;
      this.imgActor.Location = new Point(60, 540);
      this.imgActor.Name = "imgActor";
      this.imgActor.Size = new Size(60, 60);
      this.imgActor.TabIndex = 2;
      this.imgActor.TabStop = false;
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackgroundImage = (Image) Resources.map;
      this.ClientSize = new Size(953, 639);
      this.Controls.Add((Control) this.imgActor);
      this.Controls.Add((Control) this.imgSecond);
      this.Controls.Add((Control) this.imgFirst);
      this.DoubleBuffered = true;
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (BaseGame);
      this.Text = "Alice In Ceptionland - Adventure Time!";
      this.Load += new EventHandler(this.BaseGame_Load);
      this.KeyDown += new KeyEventHandler(this.BaseGame_KeyDown);
      ((ISupportInitialize) this.imgFirst).EndInit();
      ((ISupportInitialize) this.imgSecond).EndInit();
      ((ISupportInitialize) this.imgActor).EndInit();
      this.ResumeLayout(false);
    }
  }
}
