using Noesis;

namespace CoreEngine.XamlController
{
    public abstract class ControllerBase : UIElement
    {
        protected readonly Managers _managers;

        public ControllerBase()
        {
            _managers = MainWindow._managers;
        }
    }
}