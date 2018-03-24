/*
	t_object	*objs[50];
	t_vec3		pos;
	t_vec3		dir;
	t_vec3		color;
	t_vec3		intens_d;
	t_f64		phong[PHONGS];

	phong[PHONG_KA] = 0.1;


	vec3_set(&intens_d, 0.0, 0.0, 0.0);
	phong[PHONG_SHINI] = 0.0; phong[PHONG_KD] = 1.0; phong[PHONG_KS] = 0.0;
//PLANE

	vec3_set(&pos, 0., 0., -250.);
	vec3_set(&dir, 0.0, 0.0, 1.0);
	objs[36] = object_new(PLANE, &pos, &dir, 1., &color, phong, &intens_d);

	phong[PHONG_SHINI] = 12.0; phong[PHONG_KD] = 0.85; phong[PHONG_KS] = 0.4;
//CYLINDER
	vec3_set(&pos, -30, 0.0, -21.0);
	vec3_set(&dir, 0.0, 1.0, 0.0);
	vec3_set(&color, 0.50, 0.80, 0.90);
	objs[10] = object_new(CYLINDER, &pos, &dir, 3., &color, phong, &intens_d);

	vec3_set(&pos, 30, 0.0, -21.0);
	vec3_set(&dir, 0.0, 1.0, 0.0);
	vec3_set(&color, 0.50, 0.80, 0.90);
	objs[11] = object_new(CYLINDER, &pos, &dir, 3., &color, phong, &intens_d);

//CONE
	vec3_set(&pos, -50, 15, -10);
	vec3_set(&dir, 0.2, -0.2, -0.02);
	vec3_set(&color, 0.80, 0.50, 0.90);
	objs[14] = object_new(CONE, &pos, &dir, 10., &color, phong, &intens_d);

	vec3_set(&pos, 50, 5, -10);
	vec3_set(&dir, -0.2, -0.2, 0.02);
	vec3_set(&color, 0.80, 0.50, 0.90);
	objs[15] = object_new(CONE, &pos, &dir, 20., &color, phong, &intens_d);

	vec3_set(&dir, 0., 0., 0.);
	vec3_set(&color, 1.0, 1.0, 1.0);

	phong[PHONG_KD] = 0.90; phong[PHONG_KS] = 0.33;
//SPHERES
	vec3_set(&pos, 0.0, 12.5, 0.0);
	vec3_set(&color, 1.00, 0.32, 0.36);
	phong[PHONG_SHINI] = 10.0;
	objs[4] = object_new(SPHERE, &pos, &dir, 5., &color, phong, &intens_d);

	vec3_set(&pos, -10.0, 21.0, 10.0);
	vec3_set(&color, 0.50, 0.90, 0.50);
	phong[PHONG_SHINI] = 0.0;
	objs[5] = object_new(SPHERE, &pos, &dir, 3., &color, phong, &intens_d);

	vec3_set(&pos, 13, 30.0, -100.0);
	vec3_set(&color, 0.65, 0.77, 0.97);
	phong[PHONG_SHINI] = 40.0;
	phong[PHONG_KS] = 1.0;
	objs[6] = object_new(SPHERE, &pos, &dir, 40., &color, phong, &intens_d);
*/
