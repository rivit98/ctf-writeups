// Decompiled with JetBrains decompiler
// Type: AliceInCeptionland.Caterpillar
// Assembly: AliceInCeptionland, Version=1.0.0.0, Culture=neutral, PublicKeyToken=null
// MVID: 01DC5997-384E-427D-A025-8486AE92950A
// Assembly location: D:\corctf\aliceinception\AliceInCeptionland.exe

using AliceInCeptionland.Properties;

namespace AliceInCeptionland
{
    public class Caterpillar : Form
  {
    private int ticks;
    private IContainer components;
    private Button button1;
    private Label label1;
    private TextBox textBox1;
    private PictureBox imgCaterpillar;
    private Timer timer1;
    private PictureBox imgCaterpillarSmoke;
    private PictureBox imgAliceSleep;
    private Button button3;
    private Label label2;
    private Button button2;

    public string Secret { get; private set; } = string.Empty;

    public Caterpillar() => this.InitializeComponent();

    private byte rol(byte v, byte s)
    {
      byte num = (byte) ((uint) s % 8U);
      return (byte) ((int) v << (int) num | (int) v >> 8 - (int) num);
    }

    private void button1_Click(object sender, EventArgs e)
    {
      string str = "c4t3rp1114rz_s3cr3t1y_ru13_7h3_w0r1d";
      char[] array = this.textBox1.Text.Reverse<char>().ToArray<char>();
      for (int index = 0; index < array.Length; ++index)
      {
        byte num = this.rol((byte) ((uint) (byte) ((uint) (byte) ((uint) this.rol(Convert.ToByte(array[index]), (byte) 114) + 222U) ^ (uint) Convert.ToByte(str[index % str.Length])) - (uint) sbyte.MaxValue), (byte) 6);
        array[index] = Convert.ToChar(num);
      }
      if (!string.Join<char>("", ((IEnumerable<char>) array).Reverse<char>()).Equals("\0R\u009C\u007F\u0016ndC\u0005î\u0093MíÃ×\u007F\u0093\u0090\u007FS}\u00AD\u0093)ÿÃ\f0\u0093g/\u0003\u0093+Ã¶\0Rt\u007F\u0016\u0087dC\aî\u0093píÃ8\u007F\u0093\u0093\u007FSz\u00AD\u0093ÇÿÃÓ0\u0093\u0086/\u0003q"))
        return;
      this.Secret = this.textBox1.Text;
      this.label1.Visible = false;
      this.textBox1.Visible = false;
      this.button1.Visible = false;
      this.timer1.Start();
    }

    /*
\x4\xL\x1\xC\x3\x1\xS\xN\x0\xT\x4\xS\xL\x3\x3\xP\xS\x4\xV\x3\xH\x3\xR
    */

    private void timer1_Tick(object sender, EventArgs e)
    {
      ++this.ticks;
      if (this.ticks < 10)
      {
        Point location = this.imgCaterpillar.Location;
        if (this.ticks % 2 == 1)
          this.imgCaterpillar.Location = new Point(location.X, location.Y - 5);
        else
          this.imgCaterpillar.Location = new Point(location.X, location.Y + 5);
      }
      else if (this.ticks == 10)
      {
        this.imgCaterpillar.Visible = false;
        this.imgCaterpillarSmoke.Visible = true;
      }
      else if (this.ticks == 20)
      {
        this.imgCaterpillarSmoke.Visible = false;
      }
      else
      {
        if (this.ticks < 30)
          return;
        this.timer1.Stop();
        this.label2.Visible = true;
        this.button2.Visible = true;
        this.button3.Visible = true;
        this.imgAliceSleep.Visible = true;
      }
    }

    private void button2_Click(object sender, EventArgs e)
    {
      this.DialogResult = DialogResult.OK;
      this.Close();
    }

    private void button3_Click(object sender, EventArgs e)
    {
      int num = (int) MessageBox.Show((IWin32Window) this, "How many times must I repeat myself?\nCircle back and start following Alice!", "No thumb question man");
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
      ComponentResourceManager componentResourceManager = new ComponentResourceManager(typeof (Caterpillar));
      this.button1 = new Button();
      this.label1 = new Label();
      this.textBox1 = new TextBox();
      this.imgCaterpillar = new PictureBox();
      this.timer1 = new Timer(this.components);
      this.imgCaterpillarSmoke = new PictureBox();
      this.imgAliceSleep = new PictureBox();
      this.button3 = new Button();
      this.label2 = new Label();
      this.button2 = new Button();
      ((ISupportInitialize) this.imgCaterpillar).BeginInit();
      ((ISupportInitialize) this.imgCaterpillarSmoke).BeginInit();
      ((ISupportInitialize) this.imgAliceSleep).BeginInit();
      this.SuspendLayout();
      this.button1.Location = new Point(399, 316);
      this.button1.Name = "button1";
      this.button1.Size = new Size(129, 29);
      this.button1.TabIndex = 11;
      this.button1.Text = "YEEEEEET";
      this.button1.UseVisualStyleBackColor = true;
      this.button1.Click += new EventHandler(this.button1_Click);
      this.label1.AutoSize = true;
      this.label1.BackColor = Color.Transparent;
      this.label1.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label1.Location = new Point(28, 280);
      this.label1.Name = "label1";
      this.label1.Size = new Size(487, 32);
      this.label1.TabIndex = 10;
      this.label1.Text = "Oh no! Alice has noticed a worm in her cerebral cortex but her defenses are down!\r\nQuickly, enter the ejection chant to yeet that creep the fuck out of Alice's mind!";
      this.textBox1.Location = new Point(31, 321);
      this.textBox1.Name = "textBox1";
      this.textBox1.Size = new Size(362, 20);
      this.textBox1.TabIndex = 9;
      this.imgCaterpillar.BackColor = Color.Transparent;
      this.imgCaterpillar.Image = (Image) Resources.caterpillar2;
      this.imgCaterpillar.Location = new Point(109, 0);
      this.imgCaterpillar.Name = "imgCaterpillar";
      this.imgCaterpillar.Size = new Size(446, 185);
      this.imgCaterpillar.TabIndex = 12;
      this.imgCaterpillar.TabStop = false;
      this.timer1.Tick += new EventHandler(this.timer1_Tick);
      this.imgCaterpillarSmoke.BackColor = Color.Transparent;
      this.imgCaterpillarSmoke.Image = (Image) Resources.caterpillar3;
      this.imgCaterpillarSmoke.Location = new Point(109, 0);
      this.imgCaterpillarSmoke.Name = "imgCaterpillarSmoke";
      this.imgCaterpillarSmoke.Size = new Size(446, 185);
      this.imgCaterpillarSmoke.TabIndex = 13;
      this.imgCaterpillarSmoke.TabStop = false;
      this.imgCaterpillarSmoke.Visible = false;
      this.imgAliceSleep.BackColor = Color.Transparent;
      this.imgAliceSleep.Image = (Image) Resources.alice2;
      this.imgAliceSleep.Location = new Point(114, 77);
      this.imgAliceSleep.Name = "imgAliceSleep";
      this.imgAliceSleep.Size = new Size(109, 189);
      this.imgAliceSleep.TabIndex = 16;
      this.imgAliceSleep.TabStop = false;
      this.imgAliceSleep.Visible = false;
      this.button3.Location = new Point(399, 316);
      this.button3.Name = "button3";
      this.button3.Size = new Size(129, 29);
      this.button3.TabIndex = 17;
      this.button3.Text = "Give me the flag!";
      this.button3.UseVisualStyleBackColor = true;
      this.button3.Visible = false;
      this.button3.Click += new EventHandler(this.button3_Click);
      this.label2.AutoSize = true;
      this.label2.BackColor = Color.Transparent;
      this.label2.Font = new Font("Microsoft Sans Serif", 9.75f, FontStyle.Regular, GraphicsUnit.Point, (byte) 0);
      this.label2.Location = new Point(28, 298);
      this.label2.Name = "label2";
      this.label2.Size = new Size(365, 32);
      this.label2.TabIndex = 14;
      this.label2.Text = "The caterpillar released some kind of deep-sleep poison!\r\nAlice appears to be entering a deep deep dream-like state...";
      this.label2.Visible = false;
      this.button2.Location = new Point(399, 280);
      this.button2.Name = "button2";
      this.button2.Size = new Size(129, 30);
      this.button2.TabIndex = 15;
      this.button2.Text = "Follow Alice!";
      this.button2.UseVisualStyleBackColor = true;
      this.button2.Visible = false;
      this.button2.Click += new EventHandler(this.button2_Click);
      this.AutoScaleDimensions = new SizeF(6f, 13f);
      this.AutoScaleMode = AutoScaleMode.Font;
      this.BackgroundImage = (Image) Resources.alice;
      this.ClientSize = new Size(555, 370);
      this.Controls.Add((Control) this.label1);
      this.Controls.Add((Control) this.button3);
      this.Controls.Add((Control) this.imgAliceSleep);
      this.Controls.Add((Control) this.button2);
      this.Controls.Add((Control) this.button1);
      this.Controls.Add((Control) this.textBox1);
      this.Controls.Add((Control) this.imgCaterpillarSmoke);
      this.Controls.Add((Control) this.imgCaterpillar);
      this.Controls.Add((Control) this.label2);
      this.DoubleBuffered = true;
      this.FormBorderStyle = FormBorderStyle.FixedSingle;
      this.Icon = (Icon) componentResourceManager.GetObject("$this.Icon");
      this.MaximizeBox = false;
      this.MinimizeBox = false;
      this.Name = nameof (Caterpillar);
      this.Text = "Alice In Ceptionland - The Caterpillar";
      ((ISupportInitialize) this.imgCaterpillar).EndInit();
      ((ISupportInitialize) this.imgCaterpillarSmoke).EndInit();
      ((ISupportInitialize) this.imgAliceSleep).EndInit();
      this.ResumeLayout(false);
      this.PerformLayout();
    }
  }
}
