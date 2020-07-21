using OpenTK.Input;

namespace CoreEngine.Components
{
    public class NoClipCamera : CameraController
    {
        private float _speed = 100.0f;
        public NoClipCamera()
        {
        }

        public override void Init()
        {
        }

        public override void Update(float time)
        {
            
            var input = Keyboard.GetState();

            if (input.IsKeyDown(Key.W))
            {
                _Camera.Position += _Camera.Front * _speed * time; // Forward
            }

            if (input.IsKeyDown(Key.S))
            {
                _Camera.Position -= _Camera.Front * _speed * time; // Backwards
            }
            if (input.IsKeyDown(Key.A))
            {
                _Camera.Position -= _Camera.Right * _speed * time; // Left
            }
            if (input.IsKeyDown(Key.D))
            {
                _Camera.Position += _Camera.Right * _speed * time; // Right
            }
            if (input.IsKeyDown(Key.E))
            {
                _Camera.Position += _Camera.Up * _speed * time; // Up
            }
            if (input.IsKeyDown(Key.Q))
            {
                _Camera.Position -= _Camera.Up * _speed * time; // Down
            }        
        }
    }
}