#include <cstring>

namespace Math {
	template<typename T>
	INLINE T const* value_ptr(vec<T, 1> const& v)
	{
		return &(v.x);
	}

	template<typename T>
	INLINE T* value_ptr(vec<T, 1>& v)
	{
		return &(v.x);
	}

	template<typename T>
	INLINE T const* value_ptr(vec<T, 2> const& v)
	{
		return &(v.x);
	}

	template<typename T>
	INLINE T* value_ptr(vec<T, 2>& v)
	{
		return &(v.x);
	}

	template<typename T>
	INLINE T const* value_ptr(vec<T, 3> const& v)
	{
		return &(v.x);
	}

	template<typename T>
	INLINE T* value_ptr(vec<T, 3>& v)
	{
		return &(v.x);
	}

	template<typename T>
	INLINE T const* value_ptr(vec<T, 4> const& v)
	{
		return &(v.x);
	}

	template<typename T>
	INLINE T* value_ptr(vec<T, 4>& v)
	{
		return &(v.x);
	}

	template<typename T>
	INLINE T const* value_ptr(Matrix<T, 2, 2> const& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T* value_ptr(Matrix<T, 2, 2>& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T const* value_ptr(Matrix<T, 3, 3> const& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T* value_ptr(Matrix<T, 3, 3>& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T const* value_ptr(Matrix<T, 4, 4> const& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T* value_ptr(Matrix<T, 4, 4>& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T const* value_ptr(Matrix<T, 2, 3> const& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T* value_ptr(Matrix<T, 2, 3>& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T const* value_ptr(Matrix<T, 3, 2> const& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T* value_ptr(Matrix<T, 3, 2>& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T const* value_ptr(Matrix<T, 2, 4> const& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T* value_ptr(Matrix<T, 2, 4>& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T const* value_ptr(Matrix<T, 4, 2> const& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T* value_ptr(Matrix<T, 4, 2>& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T const* value_ptr(Matrix<T, 3, 4> const& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T* value_ptr(Matrix<T, 3, 4>& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T const* value_ptr(Matrix<T, 4, 3> const& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T* value_ptr(Matrix<T, 4, 3>& m)
	{
		return &(m.data[0]);
	}

	template<typename T>
	INLINE T const* value_ptr(quat<T> const& q)
	{
		return &(q[0]);
	}

	template<typename T>
	INLINE T* value_ptr(quat<T>& q)
	{
		return &(q[0]);
	}
}