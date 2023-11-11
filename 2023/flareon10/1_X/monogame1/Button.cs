using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework.Input;

namespace monogame1;

public class Button
{
	private bool _isPressed;

	private bool _isHovering;

	private MouseState _currentMouse;

	private MouseState _previousMouse;

	private Texture2D _default_texture;

	private Texture2D _highlight_texture;

	private Texture2D _pressed_texture;

	private object _tag;

	public object Tag
	{
		get
		{
			return _tag;
		}
		set
		{
			_tag = value;
		}
	}

	public Vector2 Position { get; set; }

	public Rectangle Rectangle => new Rectangle((int)Position.X, (int)Position.Y, _default_texture.Width, _default_texture.Height);

	public event EventHandler Click;

	public Button(Texture2D default_texture, Texture2D highlight_texture, Texture2D pressed_texture)
	{
		_default_texture = default_texture;
		_highlight_texture = highlight_texture;
		_pressed_texture = pressed_texture;
	}

	public void Draw(GameTime gameTime, SpriteBatch spriteBatch)
	{
		Texture2D current_texture = (_isPressed ? _pressed_texture : ((!_isHovering) ? _default_texture : _highlight_texture));
		spriteBatch.Draw(current_texture, Rectangle, Color.White);
	}

	public void Update(GameTime gameTime)
	{
		_previousMouse = _currentMouse;
		_currentMouse = Mouse.GetState();
		Rectangle mouseRectangle = new Rectangle(_currentMouse.X, _currentMouse.Y, 1, 1);
		_isHovering = false;
		if (!mouseRectangle.Intersects(Rectangle))
		{
			return;
		}
		_isHovering = true;
		if (_currentMouse.LeftButton == ButtonState.Pressed)
		{
			_isPressed = true;
			return;
		}
		_isPressed = false;
		if (_currentMouse.LeftButton == ButtonState.Released && _previousMouse.LeftButton == ButtonState.Pressed)
		{
			this.Click?.Invoke(this, new EventArgs());
		}
	}
}
