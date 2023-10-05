
#if 0
extern "C" void __cxa_throw(void* p_ptr, void* typeinfo, void (*)(void*));
template<typename T>
void my_throw(T&& t)
{
  T my_var = t;
  __cxa_throw(
    &my_var, /* typeinfo = */ nullptr, /* some void function */ nullptr);
}
#endif

extern "C"
{
  std::array<std::uint8_t, 512> storage;
  std::span<std::uint8_t> storage_left(storage);
  void* __wrap___cxa_allocate_exception(unsigned int p_size)
  {
    if (p_size > storage_left.size()) {
      return nullptr;
    }
    auto memory = storage_left.data();
    storage_left = storage_left.subspan(p_size);
    return memory;
  }
}

namespace __cxxabiv1 {
std::terminate_handler __terminate_handler = my_terminate;
}

std::array<std::uint8_t, 1024> storage;
std::span<std::uint8_t> storage_left(storage.data() + 256,
                                     storage.size() - 256);
void* __wrap___cxa_allocate_exception(unsigned int p_size)
{
  if (p_size > storage_left.size()) {
    return nullptr;
  }
  auto memory = storage_left.data();
  storage_left = storage_left.subspan(p_size);
  return memory;
}
void __wrap___cxa_free_exception(void*)
{
}