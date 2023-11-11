using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace monogame1;

public class Game1 : Game
{
	private GraphicsDeviceManager _graphics;

	private SpriteBatch _spriteBatch;

	private Button _lockButton;

	private Button[] _upButtons;

	private Button[] _downButtons;

	private DigitDisplay[] _digitDisplays;

	private BackgroundDisplay _backgroundDisplay;

	private Texture2D _flareOnLogo;

	private Rectangle _flareOnLogoRectangle;

	private int NUM_DIGITS = 2;

	public Game1()
	{
		base.Window.Title = "Welcome to Flare-On 10";
		_graphics = new GraphicsDeviceManager(this);
		base.Content.RootDirectory = "Content";
		base.IsMouseVisible = true;
	}

	protected override void Initialize()
	{
		_backgroundDisplay = new BackgroundDisplay(base.Content.Load<Texture2D>("xboard"), base.Content.Load<Texture2D>("xboard_green"), base.Content.Load<Texture2D>("xboard_red"));
		_flareOnLogo = base.Content.Load<Texture2D>("FlareOn_Logo");
		_flareOnLogoRectangle = new Rectangle(130, 30, 600, 100);
		_lockButton = new Button(base.Content.Load<Texture2D>("lock_default"), base.Content.Load<Texture2D>("lock_highlight"), base.Content.Load<Texture2D>("lock_pressed"))
		{
			Position = new Vector2(120f, 400f)
		};
		_lockButton.Click += _lockButton_Click;
		_digitDisplays = new DigitDisplay[NUM_DIGITS];
		_upButtons = new Button[NUM_DIGITS];
		_downButtons = new Button[NUM_DIGITS];
		for (int i = 0; i < NUM_DIGITS; i++)
		{
			_digitDisplays[i] = new DigitDisplay(0, base.Content.Load<Texture2D>("numbers"))
			{
				Position = new Vector2(48 * i + 15, 380f)
			};
			_upButtons[i] = new Button(base.Content.Load<Texture2D>("up_default"), base.Content.Load<Texture2D>("up_highlight"), base.Content.Load<Texture2D>("up_pressed"))
			{
				Position = new Vector2(53 * i + 5, 325f),
				Tag = i
			};
			_upButtons[i].Click += upButton_Click;
			_downButtons[i] = new Button(base.Content.Load<Texture2D>("down_default"), base.Content.Load<Texture2D>("down_highlight"), base.Content.Load<Texture2D>("down_pressed"))
			{
				Position = new Vector2(53 * i + 5, 465f),
				Tag = i
			};
			_downButtons[i].Click += downButton_Click;
		}
		base.Initialize();
		_graphics.IsFullScreen = false;
		_graphics.PreferredBackBufferWidth = 866;
		_graphics.PreferredBackBufferHeight = 869;
		_graphics.ApplyChanges();
	}

	private void downButton_Click(object sender, EventArgs e)
	{
		int buttonIndex = (int)((Button)sender).Tag;
		_digitDisplays[buttonIndex].Value--;
	}

	private void upButton_Click(object sender, EventArgs e)
	{
		int buttonIndex = (int)((Button)sender).Tag;
		_digitDisplays[buttonIndex].Value++;
	}

	private async void _lockButton_Click(object sender, EventArgs e)
	{
		if (_digitDisplays[0].Value * 10 + _digitDisplays[1].Value == 42)
		{
			_backgroundDisplay.State = BackgroundDisplay.BackgroundStates.Success;
			await MessageBox.Show("Welcome to Flare-On 10", "Congratulations!\n glorified_captcha@flare-on.com", new string[1] { "Ok" });
		}
		else
		{
			_backgroundDisplay.State = BackgroundDisplay.BackgroundStates.Failure;
		}
	}

	protected override void LoadContent()
	{
		_spriteBatch = new SpriteBatch(base.GraphicsDevice);
	}

	protected override void Update(GameTime gameTime)
	{
		if (GamePad.GetState(PlayerIndex.One).Buttons.Back == ButtonState.Pressed || Keyboard.GetState().IsKeyDown(Keys.Escape))
		{
			Exit();
		}
		_backgroundDisplay.Update(gameTime);
		_lockButton.Update(gameTime);
		Button[] upButtons = _upButtons;
		for (int i = 0; i < upButtons.Length; i++)
		{
			upButtons[i].Update(gameTime);
		}
		upButtons = _downButtons;
		for (int i = 0; i < upButtons.Length; i++)
		{
			upButtons[i].Update(gameTime);
		}
		base.Update(gameTime);
	}

	protected override void Draw(GameTime gameTime)
	{
		base.GraphicsDevice.Clear(Color.White);
		_spriteBatch.Begin();
		_backgroundDisplay.Draw(gameTime, _spriteBatch);
		_spriteBatch.Draw(_flareOnLogo, _flareOnLogoRectangle, Color.DarkGreen);
		_lockButton.Draw(gameTime, _spriteBatch);
		DigitDisplay[] digitDisplays = _digitDisplays;
		for (int i = 0; i < digitDisplays.Length; i++)
		{
			digitDisplays[i].Draw(gameTime, _spriteBatch);
		}
		Button[] upButtons = _upButtons;
		for (int i = 0; i < upButtons.Length; i++)
		{
			upButtons[i].Draw(gameTime, _spriteBatch);
		}
		upButtons = _downButtons;
		for (int i = 0; i < upButtons.Length; i++)
		{
			upButtons[i].Draw(gameTime, _spriteBatch);
		}
		_spriteBatch.End();
		base.Draw(gameTime);
	}
}
