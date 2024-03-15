// Copyright (c) 2024 Dylan Figueredo
// Distributed under the MIT license. See the LICENSE file in the project root for more information
using ElysiumEditor.Components;
using ElysiumEditor.EngineAPIStructs;
using System;
using System.Collections.Generic;
using System.Numerics;
using System.Runtime.InteropServices;
using System.Text;


namespace ElysiumEditor.EngineAPIStructs
{
    [StructLayout(LayoutKind.Sequential)]
    class TransformComponent
    {
        public Vector3 Position;
        public Vector3 Rotation;
        public Vector3 Scale = new Vector3(1, 1, 1);
    }

    [StructLayout(LayoutKind.Sequential)]
    class GameEntityDescriptor
    {
        public TransformComponent Transform = new TransformComponent();
    }
}

namespace ElysiumEditor.dllWrapper
{
    static class EngineAPI
    {
        private const string _dllName = "EngineDll.dll";

        [DllImport(_dllName)]
        private static extern int CreateGameEntity(GameEntityDescriptor desc);

        public static int CreateGameEntity(GameEntity entity)
        {
            GameEntityDescriptor desc = new GameEntityDescriptor();

            //transform
            {
                var t = entity.GetComponent<Transform>();
                desc.Transform.Rotation = t.Rotation;
                desc.Transform.Scale = t.Scale;
                desc.Transform.Position = t.Position;
            }

            return CreateGameEntity(desc);
        }

        [DllImport(_dllName)]
        private static extern int DestroyGameEntity(int id);
        public static void DestroyGameEntity(GameEntity entity)
        {
            DestroyGameEntity(entity.EntityId);
        }
    }
}
