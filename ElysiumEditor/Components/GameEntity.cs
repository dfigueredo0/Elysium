using ElysiumEditor.GameProject;
using ElysiumEditor.Utils;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Windows.Input;

namespace ElysiumEditor.Components
{
    [DataContract]
    [KnownType(typeof(Transform))]
    class GameEntity : ViewModelBase
    {
        private bool _isEnabled;
        [DataMember]   
        public bool IsEnabled
        {
            get { return _isEnabled; }
            set
            {
                if (_isEnabled != value)
                {
                    _isEnabled = value;
                    OnPropertyChanged(nameof(IsEnabled));
                }
            }
        }


        private string _name;
        [DataMember]
        public string Name
        {
            get { return _name; }
            set
            {
                if (_name != value)
                {
                    _name = value;
                    OnPropertyChanged(nameof(Name));
                }
            }
        }

        [DataMember]
        public Scene ParentScene { get; private set; }

        [DataMember(Name = nameof(Components))]
        private readonly ObservableCollection<Component> _components = new ObservableCollection<Component>();
        public ReadOnlyObservableCollection<Component> Components { get; private set; }

        public ICommand RenameCommand { get; private set; }
        public ICommand IsEnableCommand { get; private set; }

        [OnDeserialized]
        void OnDeserialized(StreamingContext context)
        {
            if(_components != null)
            {
                Components = new ReadOnlyObservableCollection<Component>(_components);
                OnPropertyChanged(nameof(Components));
            }

            RenameCommand = new RelayCommand<string>(x =>
            {
                var oldName = _name;
                Name = x;

                Project.UndoRedo.Add(new UndoRedoAction(nameof(Name), this, oldName, x, $"Rename entity '{oldName}' to '{x}'"));
            }, x => x != _name);

            IsEnableCommand = new RelayCommand<bool>(x =>
            {
                var oldVal = _isEnabled;
                IsEnabled = x;

                Project.UndoRedo.Add(new UndoRedoAction(nameof(IsEnabled), this, oldVal, x, x ? $"Enable {Name}" : $"Disable {Name}"));
            });
        }

        public GameEntity(Scene scene)
        {
            Debug.Assert(scene != null);
            ParentScene = scene;
            _components.Add(new Transform(this));
            OnDeserialized(new StreamingContext());
        }

    }

    abstract class MSEntity : ViewModelBase
    {
        private bool _enableUpdates = true;
        private bool? _isEnabled;
        public bool? IsEnabled
        {
            get { return _isEnabled; }
            set
            {
                if (_isEnabled != value)
                {
                    _isEnabled = value;
                    OnPropertyChanged(nameof(IsEnabled));
                }
            }
        }

        private string _name;
        public string  Name
        {
            get { return _name; }
            set
            {
                if (_name != value)
                {
                    _name = value;
                    OnPropertyChanged(nameof(Name));
                }
            }
        }

        private readonly ObservableCollection<IMSComponent> _components = new ObservableCollection<IMSComponent>();
        public ReadOnlyObservableCollection<IMSComponent> Components { get; }

        public List<GameEntity> SelectedEntities { get; }

        protected virtual bool UpdateGameEntities(string propertyName)
        {
            switch (propertyName)
            {
                case nameof(IsEnabled):
                    SelectedEntities.ForEach(x => x.IsEnabled = IsEnabled.Value);
                    return true;
                case nameof(Name): 
                    SelectedEntities.ForEach(x => x.Name = Name);
                    return true;
                default:
                    break;
            }
            return false;
        }

        public static float? GetMixedValue(List<GameEntity> entities, Func<GameEntity, float> getProperty)
        {
            var val = getProperty(entities.First());

            foreach (var entity in entities.Skip(1))
            {
                if (val.Equal(getProperty(entities.First())))
                    return null;
            }
            return val;
        }

        public static string GetMixedValue(List<GameEntity> entities, Func<GameEntity, string> getProperty)
        {
            var val = getProperty(entities.First());

            foreach (var entity in entities.Skip(1))
            {
                if (val != getProperty(entities.First()))
                    return null;
            }
            return val;
        }

        public static bool? GetMixedValue(List<GameEntity> entities, Func<GameEntity, bool> getProperty)
        {
            var val = getProperty(entities.First());

            foreach (var entity in entities.Skip(1))
            {
                if (val != getProperty(entities.First()))
                    return null;
            }
            return val;
        }

        protected virtual bool UpdateMSGameEntity()
        {
            IsEnabled = GetMixedValue(SelectedEntities, new Func<GameEntity, bool>(x => x.IsEnabled));
            Name = GetMixedValue(SelectedEntities, new Func<GameEntity, string>(x => x.Name));
            return true;
        }

        public void Refresh()
        {
            _enableUpdates = false;
            UpdateMSGameEntity();
            _enableUpdates = true;
        }

        public MSEntity(List<GameEntity> entities)
        {
            Debug.Assert(entities?.Any() == true);
            Components = new ReadOnlyObservableCollection<IMSComponent>(_components);
            SelectedEntities = entities;
            PropertyChanged += (s, e) => 
                {
                    if (_enableUpdates)
                        UpdateGameEntities(e.PropertyName);
                };
        }
    }

    class MSGameEntity : MSEntity
    {
        public MSGameEntity(List<GameEntity> entities) : base(entities)
        {
            Refresh();
        }
    }
}
