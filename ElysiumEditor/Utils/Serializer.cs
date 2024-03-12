using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Runtime.Serialization;
using System.Text;

namespace ElysiumEditor.Utils
{
    public static class Serializer
    {
        public static void ToFile<T>(T instance, string path)
        {
           try
            {
                using var fs = new FileStream(path, FileMode.Create);
                var serializer = new DataContractSerializer(typeof(T));
                serializer.WriteObject(fs, instance);
            } 
            catch (Exception ex)
            {
                // TODO: log error
                Debug.WriteLine(ex);
            }
        }

        public static T FromFile<T>(string path)
        {
            try
            {
                using var fs = new FileStream(path, FileMode.Open);
                var serializer = new DataContractSerializer(typeof(T));
                T instance = (T)serializer.ReadObject(fs);
                return instance;
            }
            catch (Exception ex)
            {
                // TODO: log error
                Debug.WriteLine(ex);
                return default(T);
            }
        }
    }
}
