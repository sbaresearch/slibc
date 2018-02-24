#
# spec file for package [spectemplate]
#
# Copyright (c) 2010 SUSE LINUX Products GmbH, Nuernberg, Germany.
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#

# norootforbuild

Name:           libslibc
Version:        0.9.2
Release:        1
Summary:        Secure libc implementation

License:        LGPL
Group:		System/Libraries
URL:            slibc-0.9.2.tar.gz
Source:        slibc-0.9.2.tar.gz
BuildRoot: %{_tmppath}/%{name}-%{version}-build

%if 0%{?suse_version}
BuildRequires:  libcppunit-1_12-0
BuildRequires:  libcppunit-devel
BuildRequires:  gcc-c++
BuildRequires:	doxygen
#Requires:  libcppunit-1_12-0
#Requires:  libcppunit-devel
%endif
%if 0%{?centos_version}
BuildRequires:  cppunit
BuildRequires:  cppunit-devel
BuildRequires:  gcc-c++
BuildRequires:  doxygen
#Requires:  cppunit
#Requires:  cppunit 
%endif       

%description
Slibc is a secure reimplementation of several libc functions

%package libslibc
Summary: Secure Implementation of several libc calls
Group: System/Libraries

%description libslibc
Slibc is a secure implementation of several libc functions

%package -n slibc-devel
Summary:        Development files for %{name}
Requires:       libslibc = %{version}-%{release}

%description -n slibc-devel
The %{name}-devel package contains libraries and header files for
developing applications that use %{name}.


%prep
%setup -q -n slibc-%{version}

%build
make


%install
make install DESTDIR=$RPM_BUILD_ROOT

%post -n libslibc
/sbin/ldconfig

%postun -n libslibc
/sbin/ldconfig

%post -n slibc-devel
/sbin/ldconfig

%postun -n slibc-devel
/sbin/ldconfig


%clean
rm -rf $RPM_BUILD_ROOT

%files -n libslibc
%defattr(-,root,root)  
/%{_libdir}/*.so.*
/usr/share/man/man3/*

%files -n slibc-devel
%defattr(-,root,root)
%{_prefix}/include/slibc/
