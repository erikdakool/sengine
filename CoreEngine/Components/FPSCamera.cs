using System;
using CoreEngine.Manager;
using CoreEngine.Models;
using OpenTK;
using OpenTK.Input;

namespace CoreEngine.Components
{
    public class FPSCamera : CameraController
    {
        private static float _speed = 20.0f;
        private Vector3I _currentBlock;
        private Vector3I _currentChunk;

        public FPSCamera()
        {

        }

        public override void Init()
        {
            int x = (int) _Camera.Position.X / 2;
            int y = (int) _Camera.Position.Y / 2;
            int z = (int) _Camera.Position.Z/ 2;
            
            _currentBlock = new Vector3I(x,y,z);
            
            x = (int)_Camera.Position.X/ (Chunk.Width*2);
            y = (int) _Camera.Position.Y / (Chunk.Height*2);
            z = (int)_Camera.Position.Z/ (Chunk.Length*2);
            _currentChunk = new Vector3I(x,y,z);        
        }

        public override void Update(float time)
        {
            var diff = new Vector3();
            
            //Console.WriteLine(_currentBlock + " " +_currentChunk);
            var mouse = Mouse.GetState();
            var input = Keyboard.GetState();
            
            if (input.IsKeyDown(Key.W))
            {
                diff.Z -= _speed * time; // Forward
            }

            if (input.IsKeyDown(Key.S))
            {
                diff.Z += _speed * time; // Backwards
            }
            if (input.IsKeyDown(Key.A))
            {
                diff.X -= _speed * time; // Left
            }
            if (input.IsKeyDown(Key.D))
            {
                diff.X += _speed * time; // Right
            }
            if (input.IsKeyDown(Key.E))
            {
                diff.Y += _speed * time; // Up
            }
            if (input.IsKeyDown(Key.Q))
            {
                diff.Y -= _speed * time; // Down
            }

            if (!Physics.Collision(_Camera.Position, diff))
            {
                _Camera.Position += diff;
            }
        }
    }
}