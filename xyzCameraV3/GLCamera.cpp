
#include "GLCamera.hpp"

GLCamera::GLCamera() {
    _u = Eigen::Vector3d(1, 0, 0);
    _v = Eigen::Vector3d(0, 1, 0);
    _w = Eigen::Vector3d(0, 0, 1);
    _e = Eigen::Vector3d(0, 0, 0);
    _target = Eigen::Vector3d(0, 0, -1);
    _view_matrix.setIdentity();
    _view_rotate_matrix.setIdentity();
    _view_translate_matrix.setIdentity();
}

GLCamera::~GLCamera() {

}

void GLCamera::PrintInfo() {
    std::cout << "Camera position: " << _e << "\n";
    std::cout << "u: " << _u.transpose() << "\n";
    std::cout << "v: " << _v.transpose() << "\n";
    std::cout << "w: " << _w.transpose() << "\n";
}


#pragma region(setters)
void GLCamera::SetViewTranslateMatrix(const Eigen::Vector3d& m) {
	_view_translate_matrix.block<3, 1>(0, 3) = m;
	UpdateViewMatrix();
}
void GLCamera::SetViewTranslateMatrix(const Eigen::Matrix4d& m) {
	_view_translate_matrix = m;
	UpdateViewMatrix();
}

void GLCamera::SetViewRotateMatrix(const Eigen::Matrix3d& m) {
	_view_rotate_matrix.block<3, 3>(0, 0) = m;
	UpdateViewMatrix();
}
void GLCamera::SetViewRotateMatrix(const Eigen::Matrix4d& m) {
	_view_rotate_matrix = m;
	UpdateViewMatrix();
}
void GLCamera::SetViewRotateMatrix(const Eigen::Vector3d& u, const Eigen::Vector3d& v, const Eigen::Vector3d& w) {
	Eigen::Vector3d tmp_u, tmp_v, tmp_w;
	tmp_u = u; tmp_v = v; tmp_w = w;
	tmp_u.normalize(); tmp_v.normalize(); tmp_w.normalize();
	_view_rotate_matrix.row(0) = ToHomogeneous(tmp_u);
	_view_rotate_matrix.row(1) = ToHomogeneous(tmp_v);
	_view_rotate_matrix.row(2) = ToHomogeneous(tmp_w);
	UpdateViewMatrix();
}

void GLCamera::SetViewMatrix(const Eigen::Matrix4d& m) {
	_view_matrix = m;
	_u = m.block<1, 3>(0, 0); _u.normalize();
	_v = m.block<1, 3>(1, 0); _v.normalize();
	_w = m.block<1, 3>(2, 0); _w.normalize();
	_e = m.block<3, 1>(0, 3); _e.normalize();
	_e = -_e;
}
void GLCamera::SetViewMatrix(const Eigen::Vector3d& u, const Eigen::Vector3d& v, const Eigen::Vector3d& w, const Eigen::Vector3d& e) {
	Eigen::Vector3d tmp_e, tmp_u, tmp_v, tmp_w;
	tmp_u = u; tmp_v = v; tmp_w = w; tmp_e = e;

	SetViewTranslateMatrix((Eigen::Vector3d)(-e));
	SetViewRotateMatrix(tmp_u, tmp_v, tmp_w);
}




void GLCamera::SetCamera(const Eigen::Vector3d& pos, const Eigen::Vector3d& tar) {
	Eigen::Vector3d tmp_e, tmp_u, tmp_v, tmp_w;
	tmp_e = pos;
	tmp_w = pos - tar; tmp_w.normalize();
	if (abs(tmp_e.x()) < 1e-5 && abs(tmp_e.z()) < 1e-5) {
		if (tmp_w.y() > 0) {
			tmp_v = Eigen::Vector3d(0, 0, -1);
		}
		else {
			tmp_v = Eigen::Vector3d(0, 0, 1);
		}
	}
	else
	{
		tmp_v = Eigen::Vector3d(0, 1, 0);
	}

	tmp_u = tmp_v.cross(tmp_w); tmp_u.normalize();
	tmp_v = tmp_w.cross(tmp_u); tmp_v.normalize();

	SetViewTranslateMatrix((Eigen::Vector3d)(-pos));
	SetViewRotateMatrix(tmp_u, tmp_v, tmp_w);
}
void GLCamera::SetCamera(const Eigen::Vector3d& pos, const Eigen::Vector3d& tar, const Eigen::Vector3d& upDir) {
	Eigen::Vector3d tmp_e, tmp_u, tmp_v, tmp_w;

	tmp_w = pos - tar; tmp_w.normalize();
	tmp_v = upDir; tmp_v.normalize();
	tmp_u = tmp_v.cross(tmp_w); tmp_u.normalize();

	SetViewTranslateMatrix((Eigen::Vector3d)(-pos));
	SetViewRotateMatrix(tmp_u, tmp_v, tmp_w);
}


#pragma endregion(setters)








