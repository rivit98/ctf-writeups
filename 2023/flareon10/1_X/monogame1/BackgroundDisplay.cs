using System;
using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace monogame1;

public class BackgroundDisplay
{
	public enum BackgroundStates
	{
		Default,
		Success,
		Failure
	}

	private BackgroundStates _state;

	private Texture2D _defaultTexture;

	private Texture2D _successTexture;

	private Texture2D _failureTexture;

	private double _stateChangeTime;

	private double _lastKnownGameTime;

	private const double TIMEOUT = 3000.0;

	public BackgroundStates State
	{
		get
		{
			return _state;
		}
		set
		{
			_state = value;
			_stateChangeTime = _lastKnownGameTime;
		}
	}

	private Texture2D _currentTexture
	{
		get
		{
			if (_state == BackgroundStates.Default)
			{
				return _defaultTexture;
			}
			if (_state == BackgroundStates.Success)
			{
				return _successTexture;
			}
			if (_state == BackgroundStates.Failure)
			{
				return _failureTexture;
			}
			throw new NotImplementedException();
		}
	}

	public Vector2 Position { get; set; }

	public Rectangle Rectangle => new Rectangle((int)Position.X, (int)Position.Y, _currentTexture.Width, _currentTexture.Height);

	public BackgroundDisplay(Texture2D defaultTexture, Texture2D successTexture, Texture2D failureTexture)
	{
		_defaultTexture = defaultTexture;
		_successTexture = successTexture;
		_failureTexture = failureTexture;
	}

	public void Update(GameTime gameTime)
	{
		_lastKnownGameTime = gameTime.TotalGameTime.TotalMilliseconds;
		if (State != 0 && gameTime.TotalGameTime.TotalMilliseconds - _stateChangeTime > 3000.0)
		{
			State = BackgroundStates.Default;
		}
	}

	public void Draw(GameTime gameTime, SpriteBatch spriteBatch)
	{
		spriteBatch.Draw(_currentTexture, Rectangle, Color.White);
	}
}
