using Microsoft.Xna.Framework;
using Microsoft.Xna.Framework.Graphics;

namespace monogame1;

public class DigitDisplay
{
	private bool _isChanged;

	private int _value;

	private int[] _digitOrder = new int[10] { 9, 0, 1, 2, 3, 4, 5, 6, 7, 8 };

	private Texture2D _digitsTexture;

	public int Value
	{
		get
		{
			return _value;
		}
		set
		{
			int newval = value;
			if (newval < 0)
			{
				newval = 9;
			}
			if (newval > 9)
			{
				newval = 0;
			}
			_value = newval;
		}
	}

	public Vector2 Position { get; set; }

	public Rectangle Rectangle => new Rectangle((int)Position.X, (int)Position.Y, _digitsTexture.Width / 10, _digitsTexture.Height);

	public int Width => _digitsTexture.Width;

	private Rectangle sourceRectangle => new Rectangle(_digitOrder[Value] * (_digitsTexture.Width / 10), 0, _digitsTexture.Width / 10, _digitsTexture.Height);

	public DigitDisplay(int value, Texture2D texture)
	{
		_digitsTexture = texture;
		Value = value;
	}

	public void Draw(GameTime gameTime, SpriteBatch spriteBatch)
	{
		spriteBatch.Draw(_digitsTexture, Rectangle, sourceRectangle, Color.White);
	}
}
