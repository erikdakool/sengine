﻿using System;
 using System.Threading.Tasks;
 using CoreEngine.Components;
 using OpenTK;
 using OpenTK.Graphics;
 using OpenTK.Graphics.OpenGL4;
 using OpenTK.Input;

 namespace CoreEngine
{
    public class App : GameWindow
    {
        private bool _firstMove = true;
        private Vector2 _lastPos;

        private static double frameTime = 0.0f;
        private static int fps;
         
        private double _time = DateTime.Now.Ticks;

        private Managers managers;
        private CameraController _fpsCamera;
        
        public App(int width, int height, string title)
            : base(width, height, GraphicsMode.Default, title)
        {
            managers = new Managers(new Camera(Vector3.UnitZ * 3 + new Vector3(0,32,0), Width / (float)Height));
            _fpsCamera = new NoClipCamera();
            managers.SeedManager(_fpsCamera);
        }

        protected override void OnLoad(EventArgs e)
        {
            GL.ClearColor(0.2f, 0.3f, 0.3f, 1.0f);

            GL.Enable(EnableCap.DepthTest);
            GL.Enable(EnableCap.CullFace);
            
            // We make the mouse cursor invisible so we can have proper FPS-camera movement
            CursorVisible = false;

            
            var t = new Task(() =>
            {
                managers._terrainManager.GenerateTerrain();
            });
            t.Start();
            t.Wait();

            _fpsCamera.Init();
            base.OnLoad(e);
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            var time = DateTime.Now.Ticks;
            fps++;
            frameTime += e.Time;

            if (frameTime > 1)
            {
                //Console.WriteLine(fps);
                Title = fps.ToString();
                fps = 0;
                frameTime = 0;
            }
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            
            managers._terrainManager.Draw();

            SwapBuffers();
            base.OnRenderFrame(e);
            //Console.WriteLine(DateTime.Now.Ticks -time);
        }

        protected override void OnUpdateFrame(FrameEventArgs e)
        {
            var time = DateTime.Now.Ticks;

            if (!Focused) // check to see if the window is focused
            {
                return;
            }

            var input = Keyboard.GetState();

            if (input.IsKeyDown(Key.Escape))
            {
                Exit();
            }

            const float sensitivity = 0.2f;


            // Get the mouse state
            var mouse = Mouse.GetState();

            if (_firstMove) // this bool variable is initially set to true
            {
                _lastPos = new Vector2(mouse.X, mouse.Y);
                _firstMove = false;
            }
            else
            {
                // Calculate the offset of the mouse position
                var deltaX = mouse.X - _lastPos.X;
                var deltaY = mouse.Y - _lastPos.Y;
                _lastPos = new Vector2(mouse.X, mouse.Y);

                // Apply the camera pitch and yaw (we clamp the pitch in the camera class)
                managers._Camera.Yaw += deltaX * sensitivity;
                managers._Camera.Pitch -= deltaY * sensitivity; // reversed since y-coordinates range from bottom to top
            }

            _fpsCamera.Update((float)e.Time);

            managers._terrainManager.Update();
            managers._terrainManager.InitDraw();
            base.OnUpdateFrame(e);
            //Console.WriteLine(DateTime.Now.Ticks - time);
        }

        // This function's main purpose is to set the mouse position back to the center of the window
        // every time the mouse has moved. So the cursor doesn't end up at the edge of the window where it cannot move
        // further out
        protected override void OnMouseMove(MouseMoveEventArgs e)
        {
            if (Focused) // check to see if the window is focused
            {
                Mouse.SetPosition(X + Width / 2f, Y + Height / 2f);
            }

            base.OnMouseMove(e);
        }

        // In the mouse wheel function we manage all the zooming of the camera
        // this is simply done by changing the FOV of the camera
        protected override void OnMouseWheel(MouseWheelEventArgs e)
        {
            managers._Camera.Fov -= e.DeltaPrecise;
            base.OnMouseWheel(e);
        }

        protected override void OnResize(EventArgs e)
        {
            GL.Viewport(0, 0, Width, Height);
            // We need to update the aspect ratio once the window has been resized
            managers._Camera.AspectRatio = Width / (float)Height;
            base.OnResize(e);
        }

        protected override void OnUnload(EventArgs e)
        {
            GL.BindBuffer(BufferTarget.ArrayBuffer, 0);
            GL.BindVertexArray(0);
            GL.UseProgram(0);
            managers._terrainManager.UnBind();
            base.OnUnload(e);
        }
    }
}