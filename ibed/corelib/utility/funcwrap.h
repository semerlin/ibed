#ifndef FUNCWRAP_H
#define FUNCWRAP_H

#define GETTER(name, type) type name(void) const
#define SETTER(name, type, value) void set##name(type value)

#endif // FUNCWRAP

