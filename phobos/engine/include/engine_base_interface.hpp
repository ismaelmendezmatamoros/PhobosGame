#pragma once

namespace Phobos {
    namespace Io { class IoBaseInterface; }
    namespace Window { class WindowBaseInterface; }
    namespace Graphics { class GraphicsBaseInterface; }

    class EngineBaseInterface {
        public:
        virtual Io::IoBaseInterface *getIoComponent() = 0;
        virtual Window::WindowBaseInterface *getWindowComponent() = 0;
        virtual Graphics::GraphicsBaseInterface *getGraphicsComponent() = 0;
        virtual void stopMainLoop() = 0;
        static EngineBaseInterface* getInstance() { return engineInstance; }
        protected:
        static inline EngineBaseInterface *engineInstance;
    };
}