﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using SampleFramework;
using SlimDX.Direct3D9;
using SlimDX;
using System.Drawing;

namespace Test
{
    class TestGame : Game
    {
        GraphicsDeviceManager graphicsManager;
        VertexBuffer vertexBuffer;

        Device Device
        {
            get { return graphicsManager.Device9; }
        }

        public TestGame()
        {
            graphicsManager = new GraphicsDeviceManager(this);
            DeviceSettings settings = new DeviceSettings();
            settings.BackBufferWidth = 800;
            settings.BackBufferHeight = 600;
            settings.DeviceVersion = DeviceVersion.Direct3D9;
            settings.MultisampleType = MultisampleType.TenSamples;
            settings.MultisampleQuality = 100;
            settings.Windowed = true;
            graphicsManager.ChangeDevice(settings);
        }

        protected override void LoadContent()
        {
            base.LoadContent();

            vertexBuffer = new VertexBuffer(Device, 3 * TransformedColoredVertex.SizeInBytes,
                Usage.WriteOnly, TransformedColoredVertex.Format, Pool.Managed);
            DataStream stream = vertexBuffer.Lock(0, 0, LockFlags.None);
            stream.WriteRange(BuildVertexData());
            vertexBuffer.Unlock();
        }

        protected override void UnloadContent()
        {
            base.UnloadContent();

            if (vertexBuffer != null)
                vertexBuffer.Dispose();
            vertexBuffer = null;
        }

        protected override void Draw(GameTime gameTime)
        {
            base.Draw(gameTime);

            Device.Clear(ClearFlags.Target | ClearFlags.ZBuffer, Color.Black, 1.0f, 0);
            Device.BeginScene();

            Device.SetStreamSource(0, vertexBuffer, 0, TransformedColoredVertex.SizeInBytes);
            Device.VertexFormat = TransformedColoredVertex.Format;
            Device.DrawPrimitives(PrimitiveType.TriangleList, 0, 1);

            Device.EndScene();
        }

        protected override void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (graphicsManager != null)
                    graphicsManager.Dispose();
                graphicsManager = null;
            }

            base.Dispose(disposing);
        }

        static TransformedColoredVertex[] BuildVertexData()
        {
            TransformedColoredVertex[] vertexData = new TransformedColoredVertex[3];

            vertexData[0].Position = new Vector4(400.0f, 100.0f, 0.5f, 1.0f);
            vertexData[0].Color = Color.Red.ToArgb();

            vertexData[1].Position = new Vector4(650.0f, 500.0f, 0.5f, 1.0f);
            vertexData[1].Color = Color.Blue.ToArgb();

            vertexData[2].Position = new Vector4(150.0f, 500.0f, 0.5f, 1.0f);
            vertexData[2].Color = Color.Green.ToArgb();

            return vertexData;
        }
    }
}
