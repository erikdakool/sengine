using System.IO;
using CoreEngine.NoesisAddons;
using Noesis;
using NoesisApp;
using OpenTK;
using OpenTK.Graphics;
using OpenTK.Graphics.OpenGL4;
using OpenTK.Input;
using Key = OpenTK.Input.Key;
using MouseButton = OpenTK.Input.MouseButton;
using MouseButtonEventArgs = OpenTK.Input.MouseButtonEventArgs;

namespace CoreEngine
{
    
    class MainWindow : GameWindow
    {
        private View view;
        private Renderer renderer;

        public static Managers _managers;
        
        public MainWindow() : base(1280, 720, new GraphicsMode(32, 24, 8, 1, ColorFormat.Empty, 3), "Test",
            GameWindowFlags.Default, DisplayDevice.Default, 3, 1, GraphicsContextFlags.Default)
        {
            _managers = new Managers(new Camera(Vector3.UnitZ * 3 + new Vector3(0,32,0), Width / (float)Height));
            
            VSync = VSyncMode.On;
            //WindowState = WindowState.Fullscreen;
        }

        #region Overrides of GameWindow

        protected override void OnLoad(System.EventArgs e)
        {
            GUI.Init();
            
            NoesisApp.Application.SetThemeProviders();
            Noesis.GUI.LoadApplicationResources("Theme/NoesisTheme.DarkBlue.xaml");

            
            CustomXamlProvider xamlProvider = new CustomXamlProvider();
            GUI.SetXamlProvider(xamlProvider);

            //GUI.SetTheme((ResourceDictionary)GUI.LoadXaml("SimpleStyle.xaml"));
            
            //GUI.LoadXaml("Resources/XAML/test.xaml");
            
            //GUI.SetTheme((ResourceDictionary)GUI.LoadXaml("SimpleStyle.xaml"));
            Grid content = (Grid) GUI.LoadXaml("Resources/XAML/test.xaml");
            
            Button button = (Button) content.FindName("button");
            button.Click += (object sender, RoutedEventArgs args) =>
            {
                System.Console.WriteLine("Button was clicked");
            };
            
            var stream = GUI.LoadXamlResource("Resources/XAML/test.xaml");
            using (var sr = new StreamReader(stream))
            {
                //var contents = sr.ReadToEnd();
                //content = (Grid) GUI.ParseXaml(contents);
            }
            
            view = GUI.CreateView(content);
            renderer = view.Renderer;
            renderer.Init(new RenderDeviceGL());

            view.Update(0.001); // Ensures view is updated before first render call (avoids crash)
            base.OnLoad(e);
        }

        protected override void OnUpdateFrame(FrameEventArgs e)
        {
            view.Update(e.Time);
            base.OnUpdateFrame(e);
        }

        protected override void OnRenderFrame(FrameEventArgs e)
        {
            renderer.UpdateRenderTree();
            renderer.RenderOffscreen();

            GL.Enable(EnableCap.DepthTest);
            GL.DepthFunc(DepthFunction.Lequal);
            GL.ClearDepth(1.0f);
            GL.DepthMask(true);
            GL.Disable(EnableCap.CullFace);
            GL.Disable(EnableCap.StencilTest);
            GL.Disable(EnableCap.Blend);
            GL.Disable(EnableCap.ScissorTest);

            GL.UseProgram(0);
            GL.BindFramebuffer(FramebufferTarget.Framebuffer, 0);
            GL.Viewport(0, 0, Width, Height);
            GL.ColorMask(true, true, true, true);

            GL.ClearColor(0.0f, 0.0f, 0.0f, 1.0f);
            GL.Clear(ClearBufferMask.ColorBufferBit | ClearBufferMask.DepthBufferBit);
            renderer.Render();

            SwapBuffers();
            base.OnRenderFrame(e);
        }

        protected override void OnMouseMove(MouseMoveEventArgs e)
        {
            view.MouseMove(e.X, e.Y);
        }

        protected override void OnMouseDown(MouseButtonEventArgs e)
        {
            view.MouseButtonDown(e.X, e.Y, TranslateButton(e.Button));
        }

        protected override void OnMouseUp(MouseButtonEventArgs e)
        {
            view.MouseButtonUp(e.X, e.Y, TranslateButton(e.Button));
        }

        protected override void OnKeyDown(KeyboardKeyEventArgs e)
        {
            view.KeyDown(TranslateKey(e.Key));
        }

        protected override void OnKeyUp(KeyboardKeyEventArgs e)
        {
            view.KeyUp(TranslateKey(e.Key));
            if (e.Key == Key.Escape)
                Exit();
        }

        protected override void OnKeyPress(KeyPressEventArgs e)
        {
            view.Char(e.KeyChar);
        }

        #endregion

        private static Noesis.Key TranslateKey(Key key)
        {
            switch (key)
            {
                case Key.F1: return Noesis.Key.F1;
                case Key.F2: return Noesis.Key.F2;
                case Key.F3: return Noesis.Key.F3;
                case Key.F4: return Noesis.Key.F4;
                case Key.F5: return Noesis.Key.F5;
                case Key.F6: return Noesis.Key.F6;
                case Key.F7: return Noesis.Key.F7;
                case Key.F8: return Noesis.Key.F8;
                case Key.F9: return Noesis.Key.F9;
                case Key.F10: return Noesis.Key.F10;
                case Key.F11: return Noesis.Key.F11;
                case Key.F12: return Noesis.Key.F12;
                case Key.PageUp: return Noesis.Key.Prior;
                case Key.PageDown: return Noesis.Key.Next;
                case Key.Home: return Noesis.Key.Home;
                case Key.End: return Noesis.Key.End;
                case Key.Insert: return Noesis.Key.Insert;
                case Key.Left: return Noesis.Key.Left;
                case Key.Right: return Noesis.Key.Right;
                case Key.Up: return Noesis.Key.Up;
                case Key.Down: return Noesis.Key.Down;
                case Key.Enter: return Noesis.Key.Return;
                case Key.Tab: return Noesis.Key.Tab;
                case Key.BackSpace: return Noesis.Key.Back;
                case Key.Space: return Noesis.Key.Space;
                case Key.Delete: return Noesis.Key.Delete;
            }

            return Noesis.Key.None;
        }

        private static Noesis.MouseButton TranslateButton(MouseButton button)
        {
            switch (button)
            {
                case MouseButton.Left: return Noesis.MouseButton.Left;
                case MouseButton.Right: return Noesis.MouseButton.Right;
                case MouseButton.Middle: return Noesis.MouseButton.Middle;
                default: return Noesis.MouseButton.XButton1;
            }
        }

        protected override void OnUnload(System.EventArgs e)
        {            
            renderer.Shutdown();
            GUI.Shutdown();
            base.OnUnload(e);
        }

        protected override void OnResize(System.EventArgs e)
        {
            base.OnResize(e);
            view.SetSize(Width, Height);
            base.OnResize(e);
        }
    }
}