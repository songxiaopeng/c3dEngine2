void updatePosAndDir(){
	//取得modelx的位置
	modelx.getPosInFather(pos_modelx);
	//取得modelx的朝向
	modelx.getDir(dir_modelx);
	//取得modelx2的位置
	modelx2.getPosInFather(pos_modelx2);
	//取得modelx2的朝向
	modelx2.getDir(dir_modelx2);
	//取得water的位置（要特别注意，water的高度不是pos_water[Y]，而是water.Horizon）
	water.getPosInFather(pos_water);
	//取得waterBox的位置（要特别注意，waterBox的高度不是pos_waterBox[Y]，而是waterBox.Horizon）
	waterBox.getPosInFather(pos_waterBox);
	//取得fish的位置
	fish.getPosInFather(pos_fish);
	//取得protein位置
	protein.getPosInFather(pos_protein);
	//获得主角当前位置
	pcell->getPosInFather(pos);
	//----------------------------superburst的posList
	//制作superburst的posList
	int nsuperburst=(int)psuperburstList.size();
	posList_superburst.resize(nsuperburst);
	for(int i=0;i<nsuperburst;i++){
		psuperburstList[i]->getPosInFather(posList_superburst[i].v);
	}
	//----------------------------atomburst的posList
	//制作atomburst的posList
	int natomburst=(int)patomburstList.size();
	posList_atomburst.resize(natomburst);
	for(int i=0;i<natomburst;i++){
		patomburstList[i]->getPosInFather(posList_atomburst[i].v);
	}
	//----------------------------canonball的posList
	//制作canonball的posList
	int ncannonball=(int)pcell->pcannonballList.size();
	posList_cannonball.resize(ncannonball);
	for(int i=0;i<ncannonball;i++){
		pcell->pcannonballList[i]->getPosInFather(posList_cannonball[i].v);
	}
	//can
	int ncan=(int)pcanList.size();
	posList_can.resize(ncan);
	for(int i=0;i<ncan;i++){
		pcanList[i]->getPosInFather(posList_can[i].v);
	}//得到posList_can
	//autoCell
	int nautoCell=(int)pautoCellList.size();
	posList_autoCell.resize(nautoCell);
	dirList_autoCell.resize(nautoCell);
	for(int i=0;i<nautoCell;i++){
		pautoCellList[i]->toFather(0,0,-1,0,dirList_autoCell[i].v);
		pautoCellList[i]->getPosInFather(posList_autoCell[i].v);
		//存储坐标
		pautoCellList[i]->x=posList_autoCell[i].v[X];
		pautoCellList[i]->z=posList_autoCell[i].v[Z];
	}//得到posList_autoCell和dirList_autoCell
	//amac
	int namac=(int)pamacList.size();
	posList_amac.resize(namac);
	for(int i=0;i<namac;i++){
		pamacList[i]->getPosInFather(posList_amac[i].v);
	}//得到posList_amac
	//ene
	int nene=(int)peneList.size();
	posList_ene.resize(nene);
	for(int i=0;i<nene;i++){
		peneList[i]->getPosInFather(posList_ene[i].v);
	}//得到posList_ene
	//gene
	int ngene=(int)pgeneList.size();
	posList_gene.resize(ngene);
	for(int i=0;i<ngene;i++){
		pgeneList[i]->getPosInFather(posList_gene[i].v);
	}//得到posList_gene
	//tree
	int ntree=(int)ptreeList.size();
	posList_tree.resize(ntree);
	for(int i=0;i<ntree;i++){
		ptreeList[i]->getPosInFather(posList_tree[i].v);
	}//得到posList_tree
	//arch
	int narch=(int)parchList.size();
	posList_arch.resize(narch);
	for(int i=0;i<narch;i++){
		posList_arch[i].v[X]=parchList[i]->x;
		posList_arch[i].v[Z]=parchList[i]->z;
		posList_arch[i].v[Y]=ground.getH(posList_arch[i].v[X],posList_arch[i].v[Z]);
		posList_arch[i].v[W]=1;
	}//得到posList_arch

}
void updateLODlevelAndPointOrLineSize(){//更新LOD等级或点线宽度
	//------------------根据距离选择模型版本-------------------
	float fakeDisMax=(width_mov+height)/2;
	switch(timecounter%3){//分频
	case 0:
		//tree
		{
			int n=(int)ptreeList.size();	
			for(int i=0;i<n;i++){
				Ctree&tree=*ptreeList[i];
				if(tree.visible){
					//计算tree与主角的伪距离
					float fakeDis_3d=fabs(campos_left[X]-posList_tree[i].v[X])+fabs(campos_left[Y]-posList_tree[i].v[Y])+fabs(campos_left[Z]-posList_tree[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.333){
						tree.setIndex(0);	
					}else if(fakeDis_3d<fakeDisMax*0.833){
						tree.setIndex(1);
					}else{
						tree.setIndex(2);	
					}
				}
			}
		}
		break;
	case 1:
		//autoCell
		{
			int n=(int)pautoCellList.size();
			for(int i=0;i<n;i++){
				CautoCell&autoCell=*pautoCellList[i];
				if(autoCell.visible){
					//计算autoCell与主角的伪距离
					float fakeDis_3d=fabs(campos_left[X]-posList_autoCell[i].v[X])+fabs(campos_left[Y]-posList_autoCell[i].v[Y])+fabs(campos_left[Z]-posList_autoCell[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.38){
						autoCell.setIndex(0);
						autoCell.setCoreSlice(12);
						autoCell.setEneSlice(12);

					}else if(fakeDis_3d<fakeDisMax*0.833){
						autoCell.setIndex(1);
						autoCell.setCoreSlice(6);
						autoCell.setEneSlice(6);

					}else{
						autoCell.setIndex(2);
						autoCell.setCoreSlice(3);
						autoCell.setEneSlice(3);
					}
				}

			}
		}
		break;
	case 2:
		//cannonball
		{
			int n=(int)pcell->pcannonballList.size();
			for(int i=0;i<n;i++){
				Ccannonball&cannonball=*pcell->pcannonballList[i];
				if(cannonball.visible){
					//计算cannonball与主角的伪距离
					float fakeDis_3d=fabs(campos_left[X]-posList_cannonball[i].v[X])+fabs(campos_left[Y]-posList_cannonball[i].v[Y])+fabs(campos_left[Z]-posList_cannonball[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.333){
						cannonball.ball.setSlice(6);
					}else{
						cannonball.ball.setSlice(3);
					}

				}

			}
		}
		break;
	}//end switch
	switch(timecounter%3){//分频
	case 0:
		//amac
		{
			int n=(int)pamacList.size();
			for(int i=0;i<n;i++){
				Camac&amac=*pamacList[i];
				if(amac.visible){
					//计算amac与主角的伪距离
					float fakeDis_3d=fabs(campos_left[X]-posList_amac[i].v[X])+fabs(campos_left[Y]-posList_amac[i].v[Y])+fabs(campos_left[Z]-posList_amac[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.333){
						amac.setSlice(12,6);
					}else if(fakeDis_3d<fakeDisMax*0.666){
						amac.setSlice(6,3);
					}else{
						amac.setSlice(3,3);
					}
				}

			}
		}
		break;
	case 1:
		//ene
		{
			int n=(int)peneList.size();
			for(int i=0;i<n;i++){
				Cene&ene=*peneList[i];
				if(ene.visible){
					//计算ene与主角的伪距离
					float fakeDis_3d=fabs(campos_left[X]-posList_ene[i].v[X])+fabs(campos_left[Y]-posList_ene[i].v[Y])+fabs(campos_left[Z]-posList_ene[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.333){
						ene.setSlice(12,6);
					}else if(fakeDis_3d<fakeDisMax*0.666){
						ene.setSlice(6,3);
					}else{
						ene.setSlice(3,3);
					}
				}

			}
		}
		break;
	case 2:
		//gene
		{
			int n=(int)pgeneList.size();
			for(int i=0;i<n;i++){
				Cgene&gene=*pgeneList[i];
				if(gene.visible){
					//计算gene与主角的伪距离
					float fakeDis_3d=fabs(campos_left[X]-posList_gene[i].v[X])+fabs(campos_left[Y]-posList_gene[i].v[Y])+fabs(campos_left[Z]-posList_gene[i].v[Z]);
					if(fakeDis_3d<fakeDisMax*0.333){
						gene.setSlice(12,6);
					}else if(fakeDis_3d<fakeDisMax*0.666){
						gene.setSlice(6,3);
					}else{
						gene.setSlice(3,3);
					}
				}

			}
		}
		break;
	}//end switch
	//protein
	if(protein.visible){
		//计算gene与主角的伪距离
		float fakeDis_3d=fabs(campos_left[X]-pos_protein[X])+fabs(campos_left[Y]-pos_protein[Y])+fabs(campos_left[Z]-pos_protein[Z]);
		if(fakeDis_3d<fakeDisMax*0.333){
			protein.setSlice(12,6);
		}else if(fakeDis_3d<fakeDisMax*0.666){
			protein.setSlice(6,3);
		}else{
			protein.setSlice(3,3);
		}
	}	
	//waterBox
	if(waterBox.visible){
		//计算waterBox与主角的伪距离
		float fakeDis_3d=fabs(campos_left[X]-pos_waterBox[X])+fabs(campos_left[Y]-waterBox.Horizon)+fabs(campos_left[Z]-pos_waterBox[Z]);
		if(fakeDis_3d>4300){
			waterBox.tooFar=true;
		}else{
			waterBox.tooFar=false;
		}

	}
	//water
	if(water.visible){
		//计算water与主角的伪距离
		float fakeDis_3d=fabs(pos[X]-pos_water[X])+fabs(pos[Y]-water.Horizon)+fabs(pos[Z]-pos_water[Z]);
		if(fakeDis_3d>500){
			water.tooFar=true;
		}else{
			water.tooFar=false;
		}
	}
//	cout<<water.tooFar<<endl;
	//------------superburst的LOD和pointSize
	switch(timecounter%2){//分频
	case 0:
		{
			int nsuperburst=(int)psuperburstList.size();
			for(int i=0;i<nsuperburst;i++){
				Csuperburst&superburst=*psuperburstList[i];
				if(superburst.isdied||superburst.hide||superburst.visible==false)continue;
				float superburstPos[4];
				superburst.getPosInFather(superburstPos);
				float d_2=pow2(superburstPos[X]-campos_left[X])+pow2(superburstPos[Z]-campos_left[Z]);
				float d=CarmSqrt(d_2);
				//设置doLOD	
				if(d>=4000){
					superburst.LODlevel=2;
				}else if(d>=2500){
					superburst.LODlevel=1;
				}else{
					superburst.LODlevel=0;
				}
				//设置superburst的pointSize
				if(d<500){
					float d1,s1,d2,s2;//当d=d1时size=s1,当d=d2时size=s2

					d1=500;
					s1=30;
					d2=100;
					s2=260;//150
					float a,b;//size=a*d+b中的a,b两个参数
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//本应(s1-b)/d1，d1加1的目的是防止零除
					superburst.pointSize=min(56,a*d+b);


				}else if(d>2000){
					float d1,s1,d2,s2;//当d=d1时size=s1,当d=d2时size=s2

					d1=2000;
					s1=10;
					d2=5000;
					s2=6;
					float a,b;//size=a*d+b中的a,b两个参数
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//本应(s1-b)/d1，d1加1的目的是防止零除
					superburst.pointSize=max(1,a*d+b);//要保证不过小，小于1可能导致效果错误（如发散）
				}else{//当500<=d<=2000时
					float d1,s1,d2,s2;//当d=d1时size=s1,当d=d2时size=s2

					d1=2000;
					s1=10;
					d2=500;
					s2=30;
					float a,b;//size=a*d+b中的a,b两个参数
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//本应(s1-b)/d1，d1加1的目的是防止零除
					superburst.pointSize=a*d+b;
				}
			}
		}
		break;
	case 1:
		//----------------atomburst的pointSize
		{
			int natomburst=(int)patomburstList.size();
			for(int i=0;i<natomburst;i++){
				Catomburst&atomburst=*patomburstList[i];
				//设置atomburst的pointSize
				float atomburstPos[4];
				atomburst.getPosInFather(atomburstPos);
				float d_2=pow2(atomburstPos[X]-campos_left[X])+pow2(atomburstPos[Z]-campos_left[Z]);
				float d=CarmSqrt(d_2);
				if(d<500){
					float d1,s1,d2,s2;//当d=d1时size=s1,当d=d2时size=s2

					d1=500;
					s1=16;
					d2=100;
					s2=50;
					float a,b;//size=a*d+b中的a,b两个参数
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//本应(s1-b)/d1，d1加1的目的是防止零除
					atomburst.pointSize=a*d+b;

				}else if(d>2000){
					float d1,s1,d2,s2;//当d=d1时size=s1,当d=d2时size=s2

					d1=2000;
					s1=10;
					d2=5000;
					s2=6;
					float a,b;//size=a*d+b中的a,b两个参数
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//本应(s1-b)/d1，d1加1的目的是防止零除
					atomburst.pointSize=max(1,a*d+b);//防止过小，小于1可能导致效果错误（如发散）
				}else{
					float d1,s1,d2,s2;//当d=d1时size=s1,当d=d2时size=s2

					d1=2000;
					s1=10;
					d2=500;
					s2=16;
					float a,b;//size=a*d+b中的a,b两个参数
					b=(s1*d2-s2*d1)/(d2-d1);
					a=(s1-b)/(d1+0.001);//本应(s1-b)/d1，d1加1的目的是防止零除
					atomburst.pointSize=a*d+b;
				}
			}
		}
		break;
	}
	


}
void updateLogic(){
//	printv(pos);
	
	//----------------------------制作碰撞网格
	//制作can的碰撞网格
	canCgrid.clearContent();
	canCgrid.setCenter(pos[X],pos[Z]);
	canCgrid.fillContent(posList_can);
	//制作autoCell碰撞网格
	autoCellCgrid.clearContent();
	autoCellCgrid.setCenter(pos[X],pos[Z]);
	autoCellCgrid.fillContent(posList_autoCell);
	//制作amac碰撞网格
	amacCgrid.clearContent();
	amacCgrid.setCenter(pos[X],pos[Z]);
	amacCgrid.fillContent(posList_amac);
	//制作ene碰撞网格
	eneCgrid.clearContent();
	eneCgrid.setCenter(pos[X],pos[Z]);
	eneCgrid.fillContent(posList_ene);
	//制作gene碰撞网格
	geneCgrid.clearContent();
	geneCgrid.setCenter(pos[X],pos[Z]);
	geneCgrid.fillContent(posList_gene);
	//制作tree碰撞网格
	treeCgrid.clearContent();
	treeCgrid.setCenter(pos[X],pos[Z]);
	treeCgrid.fillContent(posList_tree);
	//制作arch碰撞网格
	archCgrid.clearContent();
	archCgrid.setCenter(pos[X],pos[Z]);
	archCgrid.fillContent(posList_arch);
	
	//------------------------------碰撞检测(碰撞检测放在前面，防止各pList失效)------------------------------------------
	//autoCell之间的碰撞，使用网格机制
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell1=*pautoCellList[i];
			if(autoCell1.visible==false)continue;
			float *pos1=posList_autoCell[i].v;
			float R1=autoCell1.Rc;
			float *dir1=dirList_autoCell[i].v;
			myvector<int> clist;//碰撞列表
			autoCellCgrid.getclist(i,clist);
			//autoCell1与clist中的autoCell检测碰撞
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];//下标号
				if(J<=i)continue;//跳过比autoCell1下标号i小或相等的下标号
				CautoCell&autoCell2=*pautoCellList[J];
				if(autoCell2.visible==false)continue;
				//检测autoCell1与autoCell2的碰撞
				float *pos2=posList_autoCell[J].v;
				float R2=autoCell2.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2<=pow2(R1+R2)){//auto1与auto2碰撞
					float d=R1+R2-CarmSqrt(dis2);
					//转为背靠背
					float n1[4];//autoCell1的反射向量
					float n2[4];//autoCell2的反射向量
					sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
					sub((float(&)[4])(*pos2),(float(&)[4])(*pos1),n2);
					float *dir2=dirList_autoCell[J].v;
					float A1=getA(dir1,n1);
					float A2=getA(dir2,n2);
					autoCell1.rotloc010(A1);
					autoCell2.rotloc010(A2);
					autoCell1.movloc(0,0,-d/2);
					autoCell2.movloc(0,0,-d/2);
					break;//对于某个对象，检测到它的一个碰撞就行了，后面都这样处理
					
				}			
				
			}
		}
	}
		
	//*pcell与autoCell碰撞，使用网格机制
	{
		//获得碰撞列表
		CmyCell&myCell=*pcell;
		float R1=myCell.Rc;
		float *pos1=pos;//myCell位置
		myvector<int> clist;
		autoCellCgrid.getclist(pos1[X],pos1[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];//下标号
			CautoCell&autoCell=*pautoCellList[I];	
			if(autoCell.visible==false)continue;
			//检测autoCell与myCell的碰撞
			float *pos2=posList_autoCell[I].v;//autoCell位置
			float R2=autoCell.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<=pow2(R1+R2)){//myCell与autoCell碰撞
				if(myCell.nomatch==false){//如果myCell不是处于无敌状态
					float d=(R1+R2)-CarmSqrt(dis2);//碰撞的法向深度
					//myCell生命减少
					myCell.lifeplus(-1);
					//myCell回退一步
					//求回退向量
					float n1[4];//myCell的反射向量
					sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
					float back[4];//myCell的回退向量
					if(normalize(n1)==0)continue;
					mul(d/2,n1,back);//得到back
			//		//回退前RMmat留底
			//		float RMmat1[16];//myCell的RMmat留底
			//		matcopy(pcell->RMmat,RMmat1);
					//myCell回退
					myCell.movloc_inFather(back[X],back[Y],back[Z]);
			//		//如果myCell回退后与house发生碰撞，则须移回
			//		float _pos1[4];//移动后myCell的位置
			//		pcell->toGround(0,0,0,1,_pos1);
			//		//*pcell与house碰撞检测
			//		if(house.collisionTest_singlePoint(_pos1,pcell->Rc)>0){
			//			//恢复
			//			matcopy(RMmat1,pcell->RMmat);
			//		}
					//autoCell转身
					float n2[4]={-n1[X],-n1[Y],-n1[Z],0};//autoCell的反射向量
					float *dir2=dirList_autoCell[I].v;
					float A2=getA(dir2,n2);
					
					autoCell.rotloc010(A2);
					//autoCell前进一步
					autoCell.movloc(0,0,-d/2);
			//		//前进后位置更新
			//		float _pos2[4];
			//		autoCell.toGround(0,0,0,1,_pos2);
			//		//用autoCell的新位置进行与house碰撞检测
			//		float e_back2[4];//反弹方向
			//		float d2=house.collisionTest_multiPoint(_pos2,autoCell.Rc,e_back2);//打入深度
			//		if(d2>0){
			//			//反弹
			//			float back2[4];
			//			mul(d2,e_back2,back2);
			//			autoCell.movloc_inFather(back2[X],back2[Y],back2[Z]);
			//			
			//		}
					
				}else{//如果myCell处于无敌状态
					//autoCell消失
					autoCell.life=0;
					//autoCell叫声音
					{
						autoCell.sourceMake(13);
						autoCell.sourcePos(pos2,k_soundDis);
						autoCell.sourcePlay();
					}
				}
				break;
				
			}
		}
	}
	
	//autoCell与tree碰撞，使用网格机制
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			if(autoCell.visible==false)continue;
			float R1=autoCell.Rc;
			float *pos1=posList_autoCell[i].v;//autoCell位置
			myvector<int> clist;
			//获得碰撞列表
			treeCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];//下标号
				Ctree&tree=*ptreeList[J];	
				if(tree.visible==false)continue;
				//检测tree与myCell的碰撞
				float *pos2=posList_tree[J].v;//tree位置
				float R2=tree.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2<=pow2(R1+R2)){//myCell与tree碰撞
					//回退
					float backLen=R1+R2-CarmSqrt(dis2);//以打入深度为回退距离
					float back[4];//回退向量
					sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),back);
					back[Y]=0;//舍弃Y分量
					mul(backLen/(getLen(back)+1),back,back);//分母加1是为了防止出现0除
					//按back回退
					autoCell.movloc_inFather(back[X],back[Y],back[Z]);
		//			//如果回退后撞墙，则沿墙壁法向弹回
		//			float e_back[4];
		//			float d=house.collisionTest_singlePoint(pos1,R1,e_back);
		//			if(d>0){
		//				float back[4];
		//				mul(d,e_back,back);
		//				autoCell.movloc_inFather(back[X],back[Y],back[Z]);
		//			}
					break;
				}
			}
		}
	}
	
	//autoCell与can碰撞，使用网格机制
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			if(autoCell.visible==false)continue;
			float R1=autoCell.Rc;
			float *pos1=posList_autoCell[i].v;//autoCell位置
			myvector<int> clist;
			//获得碰撞列表
			canCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];//下标号
				Ccan&can=*pcanList[J];	
				if(can.visible==false)continue;
				//检测can与myCell的碰撞
				float *pos2=posList_can[J].v;//can位置
				float R2=can.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2<=pow2(R1+R2)){//myCell与can碰撞
					//回退
					float backLen=R1+R2-CarmSqrt(dis2);//以打入深度为回退距离
					float back[4];//回退向量
					sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),back);
					back[Y]=0;//舍弃Y分量
					mul(backLen/(getLen(back)+1),back,back);//分母加1是为了防止出现0除
					//按back回退
					autoCell.movloc_inFather(back[X],back[Y],back[Z]);
					break;
				}
			}
		}
	}
	
	
	
	//cannonball与autoCell碰撞，使用网格机制
	{
		int ncannonball=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncannonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			float *ballpos=posList_cannonball[i].v;
			float ballR=cannonball.Rc;
			//获得碰撞列表
			myvector<int> clist;
			autoCellCgrid.getclist(ballpos[X],ballpos[Z],clist);
			//处理与碰撞列表中autoCell的碰撞
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];
				CautoCell&autoCell=*pautoCellList[J];
				if(autoCell.visible==false)continue;
				//判断autoCell与cannonball是否碰撞
				float *cellpos=posList_autoCell[J].v;
				float cellR=autoCell.Rc;
				if(pow2(cellpos[X]-ballpos[X])+pow2(cellpos[Y]-ballpos[Y])+pow2(cellpos[Z]-ballpos[Z])<=pow2(cellR+ballR)){//碰撞
					//autoCell生命值减少
					autoCell.life--;
					//autoCell叫声音
					{
						autoCell.sourceMake(13);
						autoCell.sourcePos(cellpos,k_soundDis);
						autoCell.sourcePlay();
					}
					//cannonball消失
					cannonball.disapear();
					//在炮弹消失处放置一个爆炸
					int ndiedburst=(int)pdiedburstList.size();
					if(ndiedburst!=0){//如果死亡爆炸列表中还有元素
						//从pdiedburstList中取一个加入到pburstList中
						Cburst&burst=*pdiedburstList[ndiedburst-1];
						pdiedburstList.pop_back();
						burst.reSet();
						pburstList.push_back(&burst);
						ground.addchild(&burst);
						burst.setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
					}else{//如果死亡爆炸列表中已没有元素
						//重新生成炮弹
						pburstList.grow();
						pburstList[(int)pburstList.size()-1]=new Cburst();
						Cburst&burst=*pburstList[(int)pburstList.size()-1];
						ground.addchild(&burst);
						burst.setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
					}
					break;
				}
				
				
			}
		}
	}
	//cannonball与can碰撞，使用网格机制
	{
		int ncannonball=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncannonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			float *ballpos=posList_cannonball[i].v;
			float ballR=cannonball.Rc;
			//获得碰撞列表
			myvector<int> clist;
			canCgrid.getclist(ballpos[X],ballpos[Z],clist);
			//处理与碰撞列表中can的碰撞
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];
				Ccan&can=*pcanList[J];
				if(can.visible==false)continue;
				
				//判断can与cannonball是否碰撞
				float *canpos=posList_can[J].v;
				float canR=can.Rc;
				if(pow2(canpos[X]-ballpos[X])+pow2(canpos[Y]-ballpos[Y])+pow2(canpos[Z]-ballpos[Z])<=pow2(canR+ballR)){//碰撞
					//can的声音	
					{
						
						can.sourceMake(6);
						can.sourceGain(0.1);
						can.sourcePos(canpos,k_soundDis);
						can.sourcePlay();

						

					}
					if(can.life!=0){
						can.life--;	
						if(can.life==0){
							can.can.indexOfTextureID=20;
							can.dish.indexOfTextureID=17;
							//在can处放置一个原子爆炸
							Catomburst*patomburst=NULL;
							int ndiedatomburst=(int)pdiedatomburstList.size();
							if(ndiedatomburst!=0){//如果死亡原子爆炸列表中还有元素
								//从pdiedatomburstList中取一个加入到patomburstList中
								patomburst=pdiedatomburstList[ndiedatomburst-1];
								pdiedatomburstList.pop_back();
								patomburst->reSet();
								patomburstList.push_back(patomburst);
								ground.addchild(patomburst);
								patomburst->setPosInFather(canpos[X],canpos[Y]+65,canpos[Z]);
								
							}else{//如果死亡的原子爆炸列表中已没有元素
								//重新生成爆炸
								patomburstList.grow();
								patomburstList[(int)patomburstList.size()-1]=new Catomburst();
								patomburst=patomburstList[(int)patomburstList.size()-1];
								ground.addchild(patomburst);
								patomburst->setPosInFather(canpos[X],canpos[Y]+65,canpos[Z]);
								patomburst->setRc(Rc_atomburst);
						//		patomburst->bshowBB=true;
							}
							//爆炸声音
							patomburst->sourceMake(7);
							patomburst->sourcePos(canpos[X],canpos[Y]+65,canpos[Z],k_soundDis);
							patomburst->sourcePlay();
						
						}
					}
					//can消失
					cannonball.disapear();
					//在炮弹消失处放置一个爆炸
					int ndiedburst=(int)pdiedburstList.size();
					if(ndiedburst!=0){//如果死亡爆炸列表中还有元素
						//从pdiedburstList中取一个加入到pburstList中
						Cburst&burst=*pdiedburstList[ndiedburst-1];
						pdiedburstList.pop_back();
						burst.reSet();
						pburstList.push_back(&burst);
						ground.addchild(&burst);
						burst.setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
					}else{//如果死亡爆炸列表中已没有元素
						//重新生成炮弹
						pburstList.grow();
						pburstList[(int)pburstList.size()-1]=new Cburst();
						Cburst&burst=*pburstList[(int)pburstList.size()-1];
						ground.addchild(&burst);
						burst.setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
					}
					break;
				}
				
				
			}
		}
	}
	//cannonball与地面碰撞
	{
		int ncannon=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncannon;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			float *ballpos=posList_cannonball[i].v;
			float groundH=ground.getH(ballpos[X],ballpos[Z]);
			if(ballpos[Y]<=groundH){
				//cannonball消失
				cannonball.disapear();
				//在炮弹消失处放置一个爆炸
				int ndiedburst=(int)pdiedburstList.size();
				if(ndiedburst!=0){//如果死亡爆炸列表中还有元素
					//从pdiedburstList中取一个加入到pburstList中
					Cburst&burst=*pdiedburstList[ndiedburst-1];
					pdiedburstList.pop_back();
					burst.reSet();
					pburstList.push_back(&burst);
					ground.addchild(&burst);
					burst.setPosInFather(ballpos[X],groundH,ballpos[Z]);
				}else{//如果死亡爆炸列表中已没有元素
					//重新生成炮弹
					pburstList.grow();
					pburstList[(int)pburstList.size()-1]=new Cburst();
					Cburst&burst=*pburstList[(int)pburstList.size()-1];
					ground.addchild(&burst);
					burst.setPosInFather(ballpos[X],groundH,ballpos[Z]);
				}
			}
		}
	}
	//*pcell与can碰撞，使用网格机制
	{
		float*pos1=pos;//myCell位置
		float R1=pcell->Rc;
		myvector<int> clist;
		canCgrid.getclist(pos[X],pos[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];
			Ccan&can=*pcanList[I];
			if(can.visible==false)continue;
			//检测can与myCell的碰撞
			float *pos2=posList_can[I].v;//tree位置
			float R2=can.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<pow2(R1+R2)){//myCell与tree碰撞
				//回退
				float k=0.25;
				float backLen=((R1+R2)-CarmSqrt(dis2))*k;//碰撞的法向深度的k倍（软回退）
				float back[4];//回退向量
				sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),back);
				if(normalize(back)==0)continue;
				mul(backLen,back,back);
				back[Y]=0;//舍弃Y分量
				//按back回退
				pcell->movloc_inFather(back[X],back[Y],back[Z]);
				break;
			}
		}
	}
	//*pcell与amac碰撞，使用网格机制
	{
		float*pos1=pos;//myCell位置
		float R1=pcell->Rc;
		myvector<int> clist;
		amacCgrid.getclist(pos[X],pos[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];
			Camac&amac=*pamacList[I];
			if(amac.visible==false)continue;
			//检测amac与myCell的碰撞
			float *pos2=posList_amac[I].v;
			float R2=amac.Rc;
			if(pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z])<=pow2(R1+R2)){//myCell与amac碰撞
				//myCell生命增加
				pcell->lifeplus(2);
				//播放吃小物件声音
				{
					alSource3f(source_eat_small,AL_POSITION,pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
					alSourcePlay(source_eat_small);
				}
				//amac消失
				amac.disapear();
				break;
			}
		}
	}
	//*pcell与ene碰撞
	{
		float*pos1=pos;//myCell位置
		float R1=pcell->Rc;
		myvector<int> clist;
		eneCgrid.getclist(pos[X],pos[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];
			Cene&ene=*peneList[I];
			if(ene.visible==false)continue;
			//检测ene与myCell的碰撞
			float *pos2=posList_ene[I].v;
			float R2=ene.Rc;
			if(pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z])<=pow2(R1+R2)){//myCell与ene碰撞
				//myCell能量增加
				pcell->eneEatplus();
				//播放吃小物件声音
				{
					alSource3f(source_eat_small,AL_POSITION,pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
					alSourcePlay(source_eat_small);
				}
				//ene消失
				ene.disapear();
				break;
				
			}
		}
	}
	//*pcell与gene碰撞
	{
		float*pos1=pos;//myCell位置
		float R1=pcell->Rc;
		myvector<int> clist;
		geneCgrid.getclist(pos[X],pos[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];
			Cgene&gene=*pgeneList[I];
			if(gene.visible==false)continue;
			//检测gene与myCell的碰撞
			float *pos2=posList_gene[I].v;
			float R2=gene.Rc;
			if(pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z])<=pow2(R1+R2)){//myCell与gene碰撞
				//根据gene的effectID决定myCell增加何种技能
				if(gene.effectID==1){
					//跳跃
					pcell->setjumpable(true);				
				}else if(gene.effectID==2){
					//无敌
					pcell->nomatch=true;
				}else if(gene.effectID==3){
					//加速
					pcell->speedup();
				}else{
					//加分
					pcell->score+=2;
				}
				//播放吃小物件声音
				{
					alSource3f(source_eat_small,AL_POSITION,pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
					alSourcePlay(source_eat_small);
				}
				//gene消失
				gene.disapear();
				break;
				
			}
		}
	}
	
	//arch中的stick下落及地面、相互之间的碰撞检测
	{
		int narch=(int)parchList.size();
		for(int k=0;k<narch;k++){
			Carch&arch=*parchList[k];
			if(arch.freeze)continue;
			//下落（必须写最前，防止穿透地面）
			int nstick=(int)arch.pstickList.size();
			for(int i=0;i<nstick;i++){
				Cstick&stick=*arch.pstickList[i];
				stick.fall();
			}
			//stick与地面碰撞
			for(int i=0;i<nstick;i++){
				Cstick&stick=*arch.pstickList[i];
				myvector<Cv4>pList;
				myvector<Cv4>backList;
				myvector<float>deepList;
				stick.collisionWidthGround(pList,backList,deepList);
				//求质心
				float c[4];
				stick.getPc(c);	
				float Aavg[4]={0,0,0,0};
				float deepmax=0;
				int n=pList.size();
				if(n!=0){
					for(int j=0;j<n;j++){
						//----计算对角速度的贡献
						//作用点
						float *p=pList[j].v;
						//求质心到作用点的向量r
						float r[4];
						sub((float(&)[4])(*p),c,r);	
						//反弹向量
						float *n=backList[j].v;
						//打入深度
						float deep=deepList[j];
						//角位移
						float A[4];
						cross(r,n,A);
						normalize(A);
						float lenr=getLen(r);
						float lenA; 
						if(lenr==0){
							lenA=0;
						}else{
							lenA=deep/lenr*180/pi;
						}
						mul(lenA,A,A);
						add(Aavg,A,Aavg);
						if(deep>deepmax)deepmax=deep;
					}
					
					stick.movloc_inFather(0,deepmax,0);
					mul(1.0/n,Aavg,Aavg);
					stick.rot(Aavg);
					
					
				}
				
			}
			
			//stick之间的碰撞
			for(int i=0;i<nstick;i++){
				Cstick&stick1=*arch.pstickList[i];
				bool collision=false;
				for(int j=i+1;j<=(int)arch.pstickList.size()-1;j++){
					Cstick&stick2=*arch.pstickList[j];
					//判断stick1与stick2的碰撞并处理碰撞反应
					int nquad_ofstick1=(int)stick1.quadList.size();
					for(int u=0;u<nquad_ofstick1;u++){
						Cobj&quad1=stick1.quadList[u];
						//求quad1的世界坐标
						float pos1[4];
						quad1.toModel(0,0,0,1,pos1);//先转到模型空间
						stick1.toFather(pos1[X],pos1[Y],pos1[Z],pos1[W],pos1);//再转到世界空间
						int nquad_ofstick2=(int)stick2.quadList.size();
						for(int v=0;v<nquad_ofstick2;v++){
							Cobj&quad2=stick2.quadList[v];
							//求quad2的世界坐标
							float pos2[4];
							quad2.toModel(0,0,0,1,pos2);//先转到模型空间
							stick2.toFather(pos2[X],pos2[Y],pos2[Z],pos2[W],pos2);//再转到世界空间
							//判断quad1和quad2是否碰撞
							float len_2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
							if(len_2<=pow2(stick1.d/2+stick2.d/2)){//碰撞
								collision=true;
								//求碰撞点
								float p[4];
								add(pos1,pos2,p);
								mul(0.5,p,p);
								//求质心
								float c1[4];
								float c2[4];
								stick1.getPc(c1);
								stick2.getPc(c2);
								//求矢径
								float r1[4];
								float r2[4];
								sub(p,c1,r1);
								sub(p,c2,r2);
								//求反弹向量
								float n1[4];
								float n2[4];
								sub(pos1,pos2,n1);
								normalize(n1);
								sub(pos2,pos1,n2);
								normalize(n2);
								//求深度
								float len=CarmSqrt(len_2);
								float deep1=stick1.d/2+stick2.d/2-len;
								float deep2=stick1.d/2+stick2.d/2-len;
								//根据p、back和deep更新stick1和stick2
								//stick1转动
								//角位移
								float A1[4];
								cross(r1,n1,A1);
								normalize(A1);
								float lenr1=getLen(r1);
								float lenA1; 
								if(lenr1==0){
									lenA1=0;
								}else{
									lenA1=deep1/lenr1*180/pi;
								}
								mul(0.2*lenA1,A1,A1);
								stick1.rot(A1);
								//线位移
								float back1[4];
								mul(deep1,n1,back1);
								stick1.movloc_inFather(back1[X],back1[Y],back1[Z]);
								if(back1[Y]>0){
									mul(0.8,stick1.vc,stick1.vc);
									float vc1len=getLen(stick1.vc);
									if(vc1len<3){
										mul(1.0/vc1len,stick1.vc,stick1.vc);
									}
								}
								//stick2转动
								//角位移
								float A2[4];
								cross(r2,n2,A2);
								normalize(A2);
								float lenr2=getLen(r2);
								float lenA2; 
								if(lenr2==0){
									lenA2=0;
								}else{
									lenA2=deep2/lenr2*180/pi;
								}
								mul(0.2*lenA2,A2,A2);
								stick2.rot(A2);
								//线位移
								float back2[4];
								mul(deep2,n2,back2);
								stick2.movloc_inFather(back2[X],back2[Y],back2[Z]);
								if(back2[Y]>0){
									mul(0.8,stick2.vc,stick2.vc);
									float vc2len=getLen(stick2.vc);
									if(vc2len<3){
										mul(1.0/vc2len,stick2.vc,stick2.vc);
									}
								}
							}
						}
					}
					
				}
				if(collision)
				{	
					float c[4];
					stick1.getPc(c);
					float groundHorizon=ground.getH(c[X],c[Z]);
					if(c[Y]-stick1.d/2<=groundHorizon){
						stick1.movloc_inFather(0,fabs(c[Y]-stick1.d/2-groundHorizon),0);
						stick1.freeze=true;//一旦重心着地，就冻结，这样防止以后再颤动，当然，只有底层的才能冻结，但这对增加稳定性已足够
					}
				}
			}
			if(showShadow){
				arch.mesh2mesh_world();
				arch.remakeBondEdgeList(light_pos);
				arch.remakeSV(light_pos);
			}
		}
			
	}
	
		//arch与主角碰撞，使用网格机制
	{
		CmyCell&myCell=*pcell;
		float pos1[4];
		myCell.getPosInFather(pos1);
		float R1=myCell.Rc;
		myvector<int> clist;
		archCgrid.getclist(pos1[X],pos1[Z],clist);
		int nc=(int)clist.size();
		for(int k=0;k<nc;k++){
			int K=clist[k];//下标号
			Carch&arch=*parchList[K];
			if(arch.visible==false)continue;
			//检测myCell与arch是否碰撞
			float pos_arch[4];
			veccopy(posList_arch[K].v,pos_arch);
			float R_arch=Rc_arch;
			bool mycell_arch_collision=false;
			if(pow2(pos1[X]-pos_arch[X])+pow2(pos1[Y]-pos_arch[Y])+pow2(pos1[Z]-pos_arch[Z])<=pow2(R1+R_arch)){//碰撞
				mycell_arch_collision=true;
			}//得到mycell_arch_collision
			if(!mycell_arch_collision)continue;//如果不碰撞，不用再细检测，跳过
			int nstick=(int)arch.pstickList.size();
			for(int i=0;i<nstick;i++){
				Cstick&stick=*arch.pstickList[i];
				//检测stick与myCell碰撞
				//求中心距离平方
				float pos2[4];
				stick.getPosInFather(pos2);
				float R2=stick.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2>pow2(R1+R2)){//一定不碰撞
					continue;
				}
				//求stick的最大高度
				float head[4];
				stick.toFather(0,stick.len()/2,0,1,head);
				float bottom[4];
				stick.toFather(0,-stick.len()/2,0,1,bottom);
				float hmax=max(head[Y],bottom[Y]);
				if(hmax<pos[Y]){//一定不碰撞
					continue;
				}
				//否则说明满足hmax>=pos[Y]且dis2<=pow2(R1+R2)，发生碰撞	
				//处理碰撞反应
				float k=0.2;
				float d=((R1+R2)-CarmSqrt(dis2))*k;//碰撞的法向深度的k倍（软回退）
				//myCell回退
				//求回退向量
				float n1[4];//myCell的反射向量
				sub(pos1,pos2,n1);
				float back[4];
				normalize(n1);
				mul(d,n1,back);
				back[Y]=0;//舍弃Y分量
		//		//回退前RMmat留底
		//		float RMmat1[16];//myCell的RMmat留底
		//		matcopy(pcell->RMmat,RMmat1);	
				//回退
				myCell.movloc_inFather(back[X],back[Y],back[Z]);
		//		//如果myCell回退后与house发生碰撞，则须移回
		//		float _pos1[4];//移动后myCell的位置
		//		pcell->toGround(0,0,0,1,_pos1);
		//		//myCell与house碰撞检测
		//		if(house.collisionTest_singlePoint(_pos1,pcell->Rc)>0){//碰撞
		//			//恢复
		//			matcopy(RMmat1,pcell->RMmat);
		//		}else{//未碰撞
		//			//由于myCell位置发生了移动，所以更新pos1（这样做是为了更精确而防止震动，在其它简单的情况下均未这样做）
		//			veccopy(_pos1,pos1);
		//		}

			}
		}
	}

	//arch与autoCell碰撞,使用网格机制
	{
		int nautoCell=(int)pautoCellList.size();
		for(int u=0;u<nautoCell;u++){
			CautoCell&autoCell=*pautoCellList[u];
			if(autoCell.visible==false)continue;
			float pos1[4];
			autoCell.getPosInFather(pos1);
			float R1=autoCell.Rc;
			myvector<int> clist;
			archCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int k=0;k<nc;k++){
				int K=clist[k];//下标号
				Carch&arch=*parchList[K];
				if(arch.visible==false)continue;
				//检测autoCell与arch是否碰撞
				float pos_arch[4];
				veccopy(posList_arch[K].v,pos_arch);
				float R_arch=Rc_arch;
				bool autocell_arch_collision=false;
				if(pow2(pos1[X]-pos_arch[X])+pow2(pos1[Y]-pos_arch[Y])+pow2(pos1[Z]-pos_arch[Z])<=pow2(R1+R_arch)){//碰撞
					autocell_arch_collision=true;
				}//得到autocell_arch_collision
				if(!autocell_arch_collision)continue;//如果不碰撞，不用再细检测，跳过
				int nstick=(int)arch.pstickList.size();
				for(int i=0;i<nstick;i++){
					Cstick&stick=*arch.pstickList[i];
					//检测stick与autoCell碰撞
					//求中心距离平方
					float pos2[4];
					stick.getPosInFather(pos2);
					float R2=stick.Rc;
					float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
					if(dis2>pow2(R1+R2)){//一定不碰撞
						continue;
					}
					//求stick的最大高度
					float head[4];
					stick.toFather(0,stick.len()/2,0,1,head);
					float bottom[4];
					stick.toFather(0,-stick.len()/2,0,1,bottom);
					float hmax=max(head[Y],bottom[Y]);
					if(hmax<pos[Y]){//一定不碰撞
						continue;
					}
					//否则说明满足hmax>=pos[Y]且dis2<=pow2(R1+R2)，发生碰撞	
					//处理碰撞反应
					float d=(R1+R2)-CarmSqrt(dis2);//碰撞的法向深度
					//autoCell回退
					float n1[4];//myCell的反射向量
					sub(pos1,pos2,n1);
					//autoCell回退一步
					float back[4];
					normalize(n1);
					mul(d,n1,back);
					back[Y]=0;
					autoCell.movloc_inFather(back[X],back[Y],back[Z]);
					break;
					
				}
			}
		}
	}
	//cannonball与arch碰撞，使用网格机制
	{
		int ncannonball=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncannonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			//当前炮弹位置
			float *ballpos=posList_cannonball[i].v;
			//炮弹半径
			float ballR=cannonball.Rc;
			myvector<int> clist;
			archCgrid.getclist(ballpos[X],ballpos[Z],clist);
			int nc=(int)clist.size();
			for(int j=0;j<nc;j++){
				int J=clist[j];//下标号
				Carch&arch=*parchList[J];
				if(arch.visible==false)continue;
				//检测cannonball与arch是否碰撞
				//先看是否击中包围球
				float pos_arch[4];
				veccopy(posList_arch[J].v,pos_arch);
				float R_arch=Rc_arch;
				bool autocell_arch_collision=false;
				if(pow2(ballpos[X]-pos_arch[X])+pow2(ballpos[Y]-pos_arch[Y])+pow2(ballpos[Z]-pos_arch[Z])<=pow2(ballR+R_arch)){//碰撞
					autocell_arch_collision=true;
				}//得到autocell_arch_collision
				if(!autocell_arch_collision)continue;//如果不击中包围球，不用再细检测，跳过
				//再看高度是否合适
				//求arch中所有stick的至高点
				float Hmax=-inf;
				int nstick=(int)arch.pstickList.size();
				for(int u=0;u<nstick;u++){
					Cstick&stick=*arch.pstickList[u];
					//求stick的至高点
					float head[4];
					stick.toFather(0,stick.len()/2,0,1,head);
					float bottom[4];
					stick.toFather(0,-stick.len()/2,0,1,bottom);
					float hmax=max(head[Y],bottom[Y]);
					if(hmax>Hmax)Hmax=hmax;
				}//得到Hmax
				if(Hmax<ballpos[Y])continue;//如果高度不合适，跳过
				//做进一步检测
				for(int k=0;k<nstick;k++){
					Cstick&stick=*arch.pstickList[k];
					//检测cannonball与stick的包围球的碰撞
					float stickballpos[4];
					stick.getPosInFather(stickballpos);
					float stickballR=stick.Rc;
					if(pow2(stickballpos[X]-ballpos[X])+pow2(stickballpos[Y]-ballpos[Y])+pow2(stickballpos[Z]-ballpos[Z])<=pow2(stickballR+ballR)){//碰撞
						if(arch.freeze){
							arch.life--;
							if(arch.life==0){
								arch.setfreeze(false);
								//播放倒塌声音
								arch.sourceMake(8);
								arch.sourcePos(pos_arch,k_soundDis);
								arch.sourcePlay();
								//主角加分
								pcell->score+=15;
							}
						}
						//cannonball消失
						cannonball.disapear();
						//在炮弹消失处放置一个爆炸
						Cburst*pburst=NULL;
						int ndiedburst=(int)pdiedburstList.size();
						if(ndiedburst!=0){//如果死亡爆炸列表中还有元素
							//从pdiedburstList中取一个加入到pburstList中
							pburst=pdiedburstList[ndiedburst-1];
							pdiedburstList.pop_back();
							pburst->reSet();
							pburstList.push_back(pburst);
							ground.addchild(pburst);
							pburst->setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
						}else{//如果死亡爆炸列表中已没有元素
							//重新生成爆炸
							pburstList.grow();
							pburstList[(int)pburstList.size()-1]=new Cburst();
							pburst=pburstList[(int)pburstList.size()-1];
							ground.addchild(pburst);
							pburst->setPosInFather(ballpos[X],ballpos[Y],ballpos[Z]);
						}
						//为pburst播放声音
						{
							pburst->sourceMake(9);
							pburst->sourcePos(ballpos,k_soundDis);
							pburst->sourcePlay();
						}
						break;
						
					}
					
					
				}
			}
		}
	}
	//cannonball与house碰撞
	{
		int ncannonball=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncannonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			//当前炮弹位置
			float *ballpos=posList_cannonball[i].v;
			//前一时刻炮弹位置
			float ballposf[4];
			cannonball.toFather(0,0,300/2,1,ballposf);
			//判断线段ballposf--ballpos是否与house相交
			float p[4];//交点坐标
			if(house.collisionTest_lineSeg(ballposf,ballpos,p)){
				//cannonball消失
				cannonball.disapear();
				//在炮弹消失处放置一个爆炸
				Cburst*pburst=NULL;
				int ndiedburst=(int)pdiedburstList.size();
				if(ndiedburst!=0){//如果死亡爆炸列表中还有元素
					//从pdiedburstList中取一个加入到pburstList中
					pburst=pdiedburstList[ndiedburst-1];
					pdiedburstList.pop_back();
					pburst->reSet();
					pburstList.push_back(pburst);
					ground.addchild(pburst);
					pburst->setPosInFather(p[X],p[Y],p[Z]);
				}else{//如果死亡爆炸列表中已没有元素
					//重新生成炮弹
					pburstList.grow();
					pburstList[(int)pburstList.size()-1]=new Cburst();
					pburst=pburstList[(int)pburstList.size()-1];
					ground.addchild(pburst);
					pburst->setPosInFather(p[X],p[Y],p[Z]);
				}
				//pburst音效，打在墙壁上的声音
				pburst->sourceMake(9);
				pburst->sourcePos(p,k_soundDis);
				pburst->sourcePlay();
			}
		}
	}
	
	//检查各炮弹是否己达到射程
	{
		int ncanonball=(int)pcell->pcannonballList.size();
		for(int i=0;i<ncanonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			//如果距离pcell较远，则消失
			float *cannonballpos=posList_cannonball[i].v;
			float vec[4];
			sub(pos,(float(&)[4])(*cannonballpos),vec);
			if(getLen_2(vec)>=2000*2000){
				cannonball.disapear();
			}
		}
	}
	//modelx与pcell碰撞
	{
		if(modelx.visible){
			float *pos1=pos;
			float *pos2=pos_modelx;
			float R1=pcell->Rc;
			float R2=modelx.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<=pow2(R1+R2)){//碰撞
				
				float d=fabs((R1+R2)-CarmSqrt(dis2));//碰撞的法向深度
				                                     //加上fabs是为了避免d为负值，之所以会产生d为负值的情况，是因为CarmSqrt不精确
				//pcell回退一步
				//求回退向量
				float n1[4];//pcell的反射向量
				sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
				n1[Y]=0;
				float back[4];//pcell的回退向量
				if(normalize(n1)!=0){
					mul(d/2,n1,back);//得到back
					//pcell回退
					pcell->movloc_inFather(back[X],back[Y],back[Z]);
					//modelx回退
					//回退前保存矩阵
					float RMmatf[16];
					matcopy(modelx.RMmat,RMmatf);
					//回退
					modelx.movloc_inFather(-back[X],-back[Y],-back[Z]);
					//检测modelx与house的碰撞
					float _pos_modelx[4];
					modelx.getPosInFather(_pos_modelx);
					float e_back[4];
					float d=house.collisionTest_multiPoint_pcell(_pos_modelx,modelx.Rc,e_back);//必须用multiPoint，否则可能会穿墙
					//原因可能是singlePoint中回退向量的计算不准确从而导致错误的回退方向有关
					if(d>0){
						//恢复
						matcopy(RMmatf,modelx.RMmat);
					}
					//声音
					bool allstopped;//是否两个声音都停止了
					ALint state1;
					alGetSourcei(source_modelx_hellow_i_m_beavis, AL_SOURCE_STATE,&state1);
					ALint state2;
					alGetSourcei(source_modelx_what_are_you_doing, AL_SOURCE_STATE,&state2);
					if((state1==AL_STOPPED||state1==AL_INITIAL)&&(state2==AL_STOPPED||state2==AL_INITIAL)){
						allstopped=true;
					}else{
						allstopped=false;
					}
					if(allstopped){
						//根据modelx与pcell的朝向决定播放哪个声音
						float dir_modelx[4];
						modelx.getDir(dir_modelx);
						if(dot(n1,dir_modelx)>=0){//迎面走来
							//播放hellow, i'm beavis
							alSource3f(source_modelx_hellow_i_m_beavis,AL_POSITION,pos_modelx[X]*k_soundDis,pos_modelx[Y]*k_soundDis,pos_modelx[Z]*k_soundDis);
							alSourcePlay(source_modelx_hellow_i_m_beavis);
						}else{//追尾
							//播放what are you doing
							alSource3f(source_modelx_what_are_you_doing,AL_POSITION,pos_modelx[X]*k_soundDis,pos_modelx[Y]*k_soundDis,pos_modelx[Z]*k_soundDis);
							alSourcePlay(source_modelx_what_are_you_doing);
						}	
					}	
				}
			}
		}	
	}
	//modelx与modelx2碰撞
	{
		if(modelx.visible){
			float *pos1=pos_modelx;
			float *pos2=pos_modelx2;
			float R1=modelx.Rc;
			float R2=modelx2.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<=pow2(R1+R2)){//碰撞
				
				float d=fabs((R1+R2)-CarmSqrt(dis2));//碰撞的法向深度
				                                     //加上fabs是为了避免d为负值，之所以会产生d为负值的情况，是因为CarmSqrt不精确
				float n1[4];//modelx的反射向量
				sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
				n1[Y]=0;
				float back[4];//modelx的回退向量
				if(normalize(n1)!=0){
					mul(d,n1,back);//得到back
					//modelx回退
					modelx.movloc_inFather(back[X],back[Y],back[Z]);
				}
			}
		}	
	}
	//modelx2与pcell碰撞
	{
		if(modelx2.visible){
			float *pos1=pos;
			float *pos2=pos_modelx2;
			float R1=pcell->Rc;
			float R2=modelx2.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<=pow2(R1+R2)){//碰撞
				
				float d=fabs((R1+R2)-CarmSqrt(dis2));//碰撞的法向深度
				                                     //加上fabs是为了避免d为负值，之所以会产生d为负值的情况，是因为CarmSqrt不精确
				//pcell回退一步
				//求回退向量
				float n1[4];//pcell的反射向量
				sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
				n1[Y]=0;
				float back[4];//pcell的回退向量
				if(normalize(n1)!=0){
					mul(d,n1,back);//得到back
					//pcell回退
					pcell->movloc_inFather(back[X],back[Y],back[Z]);
				}
			}
		}	
	}
	//modelx与arch碰撞，使用网格机制
	{
		if(modelx.visible){
			float *pos1=pos_modelx;
			float R1=modelx.Rc;
			myvector<int> clist;
			archCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int k=0;k<nc;k++){
				int K=clist[k];//下标号
				Carch&arch=*parchList[K];
				if(arch.visible==false)continue;
				//检测modelx与arch是否碰撞
				float pos_arch[4];
				veccopy(posList_arch[K].v,pos_arch);
				float R_arch=Rc_arch/2;
				float dis2=pow2(pos1[X]-pos_arch[X])+pow2(pos1[Y]-pos_arch[Y])+pow2(pos1[Z]-pos_arch[Z]);
				if(dis2<=pow2(R1+R_arch)){//碰撞
					//处理碰撞反应
					float k=0.2;
					float d=((R1+R_arch)-CarmSqrt(dis2))*k;//碰撞的法向深度的k倍（软回退）
					//modelx回退
					//求回退向量
					float n1[4];//modelx的反射向量
					sub((float(&)[4])(*pos1),pos_arch,n1);
					float back[4];
					normalize(n1);
					mul(d,n1,back);
					back[Y]=0;//舍弃Y分量
					//回退
					modelx.movloc_inFather(back[X],back[Y],back[Z]);
				
					
				}
			}
		}
	}
	//modelx与autoCell碰撞，使用网格机制
	{
		if(modelx.visible){
			//获得碰撞列表
			float R1=modelx.Rc;
			float *pos1=pos_modelx;
			myvector<int> clist;
			autoCellCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int i=0;i<nc;i++){
				int I=clist[i];//下标号
				CautoCell&autoCell=*pautoCellList[I];	
				if(autoCell.visible==false)continue;
				//检测autoCell与modelx的碰撞
				float *pos2=posList_autoCell[I].v;//autoCell位置
				float R2=autoCell.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2<=pow2(R1+R2)){//modelx与autoCell碰撞
					float d=fabs((R1+R2)-CarmSqrt(dis2));//碰撞的法向深度
					//modelx回退一步
					//求回退向量
					float n1[4];//modelx的反射向量
					sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),n1);
					n1[Y]=0;
					float back[4];//modelx的回退向量
					if(normalize(n1)==0)continue;
					mul(d/2,n1,back);//得到back
					//modelx回退
					modelx.movloc_inFather(back[X],back[Y],back[Z]);
					//autoCell转身
					float n2[4]={-n1[X],-n1[Y],-n1[Z],0};//autoCell的反射向量
					float *dir2=dirList_autoCell[I].v;
					float A2=getA(dir2,n2);
					autoCell.rotloc010(A2);
					//autoCell前进一步
					autoCell.movloc(0,0,-d/2);
					
					break;
					
				}
			}
		}
	}
	//modelx2与autoCell碰撞，使用网格机制
	{
		if(modelx2.visible){
			//获得碰撞列表
			float R1=modelx2.Rc;
			float *pos1=pos_modelx2;
			myvector<int> clist;
			autoCellCgrid.getclist(pos1[X],pos1[Z],clist);
			int nc=(int)clist.size();
			for(int i=0;i<nc;i++){
				int I=clist[i];//下标号
				CautoCell&autoCell=*pautoCellList[I];	
				if(autoCell.visible==false)continue;
				//检测autoCell与modelx的碰撞
				float *pos2=posList_autoCell[I].v;//autoCell位置
				float R2=autoCell.Rc;
				float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
				if(dis2<=pow2(R1+R2)){//modelx与autoCell碰撞
					float d=fabs((R1+R2)-CarmSqrt(dis2));//碰撞的法向深度
					//求回退向量
					float n2[4];//autoCell的反射向量
					sub((float(&)[4])(*pos2),(float(&)[4])(*pos1),n2);
					n2[Y]=0;
					//autoCell转身
					float *dir2=dirList_autoCell[I].v;
					float A2=getA(dir2,n2);
					autoCell.rotloc010(A2);
					//autoCell前进一步
					autoCell.movloc(0,0,-d);
					
					break;
					
				}
			}
		}
	}
	
	
	//metalBall与pcell碰撞
	{
		if(metalBall.visible){
			float *pos1=pos;
			float pos2[4];
			metalBall.getPosInFather(pos2);
			float R1=pcell->Rc;
			float R2=metalBall.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<=pow2(R1+R2)){//碰撞
				
				float d=fabs((R1+R2)-CarmSqrt(dis2));//碰撞的法向深度
				                                     //加上fabs是为了避免d为负值，之所以会产生d为负值的情况，是因为CarmSqrt不精确
				//pcell回退一步
				//求回退向量
				float n1[4];//pcell的反射向量
				sub((float(&)[4])(*pos1),pos2,n1);
				n1[Y]=0;
				float back[4];//pcell的回退向量
				if(normalize(n1)!=0){
					mul(d,n1,back);//得到back
					//pcell回退
					pcell->movloc_inFather(back[X],back[Y],back[Z]);
				}
			}
		}	
	}
	//--------------------如果can或者arch离modelx2过近，则进行移动，让其距离足够远
	//如果can离modelx2过近，则移动can
	{
		int nCan=(int)pcanList.size();
		for(int i=0;i<nCan;i++){
			Ccan&can=*pcanList[i];
			float canX=posList_can[i].v[X];
			float canZ=posList_can[i].v[Z];
			float m2X=pos_modelx2[X];
			float m2Z=pos_modelx2[Z];
			float d=CarmSqrt(pow2(canX-m2X)+pow2(canZ-m2Z));
			if(d<=modelx2.Rc+Rc_can){
				//对can进行移动
				//求回退向量
				float back[4]={canX-m2X,0,canZ-m2Z,0};
				normalize(back);
				mul(d,back,back);
				//对can进行回退
				can.movloc_inFather(back[X],back[Y],back[Z]);
			}
			
		}
	}
	//如果arch离modelx2过近，则移动arch
	{
		int nArch=(int)parchList.size();
		for(int i=0;i<nArch;i++){
			Carch&arch=*parchList[i];
			float archX=posList_arch[i].v[X];
			float archZ=posList_arch[i].v[Z];
			float m2X=pos_modelx2[X];
			float m2Z=pos_modelx2[Z];
			float d=CarmSqrt(pow2(archX-m2X)+pow2(archZ-m2Z));
			if(d<=modelx2.Rc+Rc_arch){
				//对carch进行移动
				//求回退向量
				float back[4]={archX-m2X,0,archZ-m2Z,0};
				normalize(back);
				mul(d,back,back);
				//对can进行回退
				arch.movloc_inFather(back[X],back[Y],back[Z]);
				arch.storexz(arch.x+back[X],arch.z+back[Z]);//**
			}
			
		}
	}
	//--------------------移动----------------------------------
	//modelx运动
	{
		//但不管可不可见，都要移动并保持落到地面上
		if(modelx.visible){
			modelx.autoMov(house);
		}else{
			modelx.autoMov_whenVisibleIsFalse();
		}
		modelx.downToGround_soft();
		//不管可见与否，都是进行动画，反正动动画行进不需要任何开销，只是时间++而已
		modelx.animationAdvance_rollback(40);
		
	//	cout<<"modelx.visible:"<<modelx.visible<<endl;
	//	cout<<"modelx.visible_reflect:"<<modelx.visible_reflect<<endl;

	}
	//modelx2
	{
	//	modelx2.downToGround_soft();
		//不管可见与否都播动画，反正播动画不需任何开销，仅是时间++而已
		modelx2.animationAdvance_rollback(40);
			
		
		//求pcell到modelx2的距离平方
		float d2=pow2(pos[X]-pos_modelx2[X])+pow2(pos[Y]-pos_modelx2[Y])+pow2(pos[Z]-pos_modelx2[Z]);
		const float peakValue=6;
		const float maxDis=2000;
		const float k=-peakValue/maxDis;
		float d=fabs(CarmSqrt(d2));
		float currentValue=max(0,peakValue+k*d);
		alSourcef(source_music, AL_GAIN,currentValue);
		if(currentValue>0){//有音
			ALint state;
			alGetSourcei(source_music, AL_SOURCE_STATE,&state);
			switch(state){//AL_SOURCE_STATE只有这四种
			case AL_INITIAL:
			case AL_PAUSED:
			case AL_STOPPED:
				alSourcePlay(source_music);
				break;
			case AL_PLAYING:
				break;
			}
			//更新声源坐标
			alSource3f(source_music,AL_POSITION,pos_modelx2[X]*k_soundDis,pos_modelx2[Y]*k_soundDis,pos_modelx2[Z]*k_soundDis);
		}else{//无音
			alSourcePause(source_music);
		}
		
	}
	//fish游动
	if(fish.visible){
		fish.shakeBody(5);
		fish.updateSkin();
	}	
	//无论是否可见，都要移动
	fish.autoMov(house);
	//更新fish声源坐标
	{
		//求pcell到fish的距离平方
		float d2=pow2(pos[X]-pos_fish[X])+pow2(pos[Y]-pos_fish[Y])+pow2(pos[Z]-pos_fish[Z]);
		const float peakValue=3.5;
		const float maxDis=3200;
		const float k=-peakValue/maxDis;
		float d=fabs(CarmSqrt(d2));
		float currentValue=max(0,peakValue+k*d);
		alSourcef(source_fish_move_on_water, AL_GAIN,currentValue);
		if(currentValue>0){//有音
			ALint state;
			alGetSourcei(source_fish_move_on_water, AL_SOURCE_STATE,&state);
			switch(state){//AL_SOURCE_STATE只有这四种
			case AL_INITIAL:
			case AL_PAUSED:
			case AL_STOPPED:
				alSourcePlay(source_fish_move_on_water);
				break;
			case AL_PLAYING:
				break;
			}
			//更新声源坐标
			alSource3f(source_fish_move_on_water,AL_POSITION,pos_fish[X]*k_soundDis,pos_fish[Y]*k_soundDis,pos_fish[Z]*k_soundDis);
		}else{//无音
			alSourcePause(source_fish_move_on_water);
		}
	}


	//原子爆炸
	{
		int natomburst=(int)patomburstList.size();
		for(int i=0;i<natomburst;i++){
			Catomburst&atomburst=*patomburstList[i];
			atomburst.burst();
			//设置atomburst的各compball颜色
			{
				atomburst.updateColorOfcompballs();
			}
		}

	}
	//导弹飞行
	{
		int nbigcannon=(int)pbigcannonList.size();
		for(int i=0;i<nbigcannon;i++){
			Cbigcannon&bigcannon=*pbigcannonList[i];
			if(bigcannon.visible){
				bigcannon.vy+=5;
				float bigcannonposf[4];
				bigcannon.getPosInFather(bigcannonposf);
				bigcannon.movloc(0,-bigcannon.vy,-200);
				bigcannon.burst();
			
				float bigcannonpos[4];
				bigcannon.getPosInFather(bigcannonpos);
				bigcannon.sourcePos(bigcannonpos,k_soundDis);//更新声源位置
				float waterH=water.Horizon;
				float groundH=ground.getH(bigcannonpos[X],bigcannonpos[Z]);
				if(groundH==inf){//如果导弹射得太远，可能远处的地面还没生成，此时返回inf，要进行判断，改为-inf，以便后面取max时被忽略掉
					groundH=-inf;
				}
				float H=max(waterH,groundH);
				if(bigcannonpos[Y]<H){//与地面碰撞
					//将bigcannon设置为不可见
					bigcannon.visible=false;
					//停止声音播放
					ALint state=bigcannon.sourceState();
					if(state==AL_PLAYING||state==AL_PAUSED){
						bigcannon.sourceStop();
					}
					//放置一个superburst
					//生成superburst
					Csuperburst*psuperburst=NULL;
					//如果爆炸位置离campos_left太近，则生成球型爆炸，否则随机生成球形爆炸或蘑菇型爆炸
					int type;
					float d2=pow2(bigcannonpos[X]-campos_left[X])+pow2(bigcannonpos[Z]-campos_left[Z]);
					if(d2<=2000*2000){
						type=1;
					}else{
						type=rand()%2;
					}
				
					if(type==0){
						//从psuperburstList_mushroom中取一个isdied的
						for(int j=0;j<nsuperburstMax;j++){
							Csuperburst&superburst=*psuperburstList_mushroom[j];
							if(superburst.isdied){
								psuperburst=&superburst;
								break;
							}
						}//得到psuperburst
					
					}else{//type==1
						//从psuperburstList_ball中取一个isdied的
						for(int j=0;j<nsuperburstMax;j++){
							Csuperburst&superburst=*psuperburstList_ball[j];
							if(superburst.isdied){
								psuperburst=&superburst;
								break;
							}
						}//得到psuperburst

					}
					if(psuperburst==NULL){
					//	cout<<"error: psuperburst==NULL"<<endl;
					
					}else{//psuerburst!=NULL
						psuperburst->reSet();
						//制作superburst
						psuperburst->setPosInFather(bigcannonpos[X],H-45,bigcannonpos[Z]);
						//将psuperburst加入到场景树
						ground.addchild(psuperburst);
						//将psuperburst加入到psuperburstList
						psuperburstList.push_back(psuperburst);
						//对psuperburst建立声音
						psuperburst->sourceMake(3);
						psuperburst->sourcePos(bigcannonpos[X],H-45,bigcannonpos[Z],k_soundDis);
						psuperburst->sourcePlay();
					}

					
				}else{//不与地面碰撞
					int type;
					bool collision=false;
					//检测是否与天花板碰撞或地板碰撞
					float houseCeilH=house.getH_ceil(bigcannonposf);//前一时刻所在bsp节点的天花板高度
					if(bigcannonpos[Y]>=houseCeilH){//与天花板碰撞
						type=rand()%2;
						collision=true;
					}else{//不与天花板碰撞
						//检测是否与地地板碰撞
						float houseFloorH=house.getH_floor(bigcannonposf);//前一时刻所在bsp节点的地板高度
						if(bigcannonpos[Y]<=houseFloorH){//与地板碰撞
							type=rand()%2;
							collision=true;
						}else{//不与地板碰撞
							//检查是否与墙壁碰撞
							float e_back[4];
							if(house.collisionTest_singlePoint(bigcannonpos,Rc_bigcannon,e_back)!=-1){
								type=1;
								collision=true;	
							}
						}
					}
					//根据collision作出反应
					if(collision){		
						//将bigcannon设置为不可见
						bigcannon.visible=false;
						//声音停止
						bigcannon.sourceStop();
						//放置一个superburst
						//生成superburst
						Csuperburst*psuperburst=NULL;
						if(type==0){
							//从psuperburstList_mushroom中取一个isdied的
							for(int j=0;j<nsuperburstMax;j++){
								Csuperburst&superburst=*psuperburstList_mushroom[j];
								if(superburst.isdied){
									psuperburst=&superburst;
									break;
								}
							}//得到psuperburst
							
						}else{//type==1
							//从psuperburstList_ball中取一个isdied的
							for(int j=0;j<nsuperburstMax;j++){
								Csuperburst&superburst=*psuperburstList_ball[j];
								if(superburst.isdied){
									psuperburst=&superburst;
									break;
								}
							}//得到psuperburst
							
						}
						if(psuperburst==NULL){
						//	cout<<"error: psuperburst==NULL"<<endl;
							
						}else{//psuerburst!=NULL
							psuperburst->reSet();
							//制作superburst
							float H;
							if(type==0){
								H=bigcannonpos[Y]-13;
							}else{
								H=bigcannonpos[Y];
							}
							psuperburst->setPosInFather(bigcannonpos[X],H,bigcannonpos[Z]);
							//将psuperburst加入到场景树
							ground.addchild(psuperburst);
							//将psuperburst加入到psuperburstList
							psuperburstList.push_back(psuperburst);
							//对psuperburst建立声音
							psuperburst->sourceMake(3);
							float pos[4]={bigcannonpos[X],H,bigcannonpos[Z],1};
							psuperburst->sourcePos(pos,k_soundDis);
							psuperburst->sourcePlay();
						}
						
					}
					
				}
				
				
			}
		}
	}

	//限制大原子爆炸数量
	{
		const int nsuperburst=(int)psuperburstList.size();
		if(nsuperburst>nsuperburstMax*0.6){
			//将psuperburstList[0]设置为died
			psuperburstList[0]->setDied(true);
		}
	}
	//***大原子爆炸
	{

		int nsuperburst=(int)psuperburstList.size();
		for(int i=0;i<nsuperburst;i++){
			Csuperburst&superburst=*psuperburstList[i];
			superburst.burst();
	//		if(superburst.isdied)superburst.setVisible(false);
			if(superburst.isdied||superburst.hide||superburst.visible==false)continue;
			//设置superburst的各compball颜色
			{
				superburst.updateColorOfcompballs();
			}
		}
		//搜索psuperburstList中最后一个不为died的superburst
		{
			Csuperburst*psuperburst=NULL;
			for(int i=nsuperburst-1;i>=0;i--){
				Csuperburst&superburst=*psuperburstList[i];
				if(!superburst.isdied){
					psuperburst=&superburst;
					break;
				}
			}//得到psuperburst
			if(psuperburst!=NULL){
				//用最psuperburst设置天空颜色
				float fogColor[4];
				switch(psuperburst->stage){
				case 0:
					init4(fogColor,0.3,0.3,0.4,0.5);
					glFogfv(GL_FOG_COLOR, fogColor);
					glFogf(GL_FOG_DENSITY, 0.0003f);//雾的浓度，用于指数模式中
					glass.alpha=0;
					glass.visible=false;
			//		skyball.turnRed=false;
					break;
				case 1:
					init4(fogColor,1,0.5,0,1);
					glFogfv(GL_FOG_COLOR, fogColor);
					glFogf(GL_FOG_DENSITY, 0.00038f);//雾的浓度，用于指数模式中
					glass.visible=true;
					glass.alpha=0.25;
			//		skyball.turnRed=true;
					break;
				case 2:
					{
						float k=(psuperburst->timercount-psuperburst->duringTime*0.65)*1.0/(psuperburst->duringTime*(1-0.65)+psuperburst->delayTime);
						init4(fogColor,1+(0.3-1)*k,0.5+(0.3-0.5)*k,0+(0.4-0)*k,1);
						glFogfv(GL_FOG_COLOR, fogColor);
						glFogf(GL_FOG_DENSITY, 0.00038f-0.0001*k);//雾的浓度，用于指数模式中 
						glass.visible=true;
						glass.alpha=0.25+k*(0-0.25);
						
			//			skyball.turnRed=true;
					}
					break;
				}
				
			}
			
		}
	

	}
	//爆炸
	{
		int nburst=(int)pburstList.size();
		for(int i=0;i<nburst;i++){
			pburstList[i]->burst();
		}
	}
	//气泡升起
	{
		if(water.visible){//水可见时才气泡上升
			int nbubble=(int)pbubbleList.size();
			for(int i=0;i<nbubble;i++){
				pbubbleList[i]->rise();
			}
		}
	}
	
	
	//液滴扩散
	{
		int ndrop=(int)pdropList.size();
		for(int i=0;i<ndrop;i++){
			pdropList[i]->diffuse();
		}
	}
	//将出界的modelx移到界内
	{
		float width_mov_modelx=width_mov*0.9;
		float height_mov_modelx=height_mov*0.9;
		float pos_modelx[4];
		modelx.getPosInFather(pos_modelx);
		bool moved=false;
		if(pos_modelx[X]<pos[X]-(width_mov_modelx)/2){
			modelx.movloc_inFather(width_mov_modelx,0,0);
			moved=true;
		}
		if(pos_modelx[Z]<pos[Z]-(height_mov_modelx)/2){
			modelx.movloc_inFather(0,0,height_mov_modelx);
			moved=true;
		}
		if(pos_modelx[X]>pos[X]+(width_mov_modelx)/2){
			modelx.movloc_inFather(-width_mov_modelx,0,0);
			moved=true;
		}
		if(pos_modelx[Z]>pos[Z]+(height_mov_modelx)/2){
			modelx.movloc_inFather(0,0,-height_mov_modelx);
			moved=true;
		}
		if(moved)modelx.downToGround_soft();
		

	}
	//将出界的tree移到界内
	{
		int ntree=(int)ptreeList.size();
		for(int i=0;i<ntree;i++){
			Ctree&tree=*ptreeList[i];
			float x=posList_tree[i].v[X];
			float z=posList_tree[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov)/2){
				tree.movloc_inFather(width_mov,0,0);
				moved=true;
			}
			if(z<pos[Z]-(height_mov)/2){
				tree.movloc_inFather(0,0,height_mov);
				moved=true;
			}
			if(x>pos[X]+(width_mov)/2){
				tree.movloc_inFather(-width_mov,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov)/2){
				tree.movloc_inFather(0,0,-height_mov);
				moved=true;
			}
			if(moved){
				float treenewpos[4];
				tree.getPosInFather(treenewpos);
				//着陆
				float groundHorizon=ground.getH(treenewpos[X],treenewpos[Z]);
				if(groundHorizon>water.Horizon){
					tree.downToGround(0,false);
				}else{
					tree.downToWaterSurface();
					
				}
			}
			
		}
	}

	int width_mov_molecule=width_mov;
	int height_mov_molecule=height_mov;

	
	//将出界的amac移到界内
	{
		int namac=(int)pamacList.size();
		for(int i=0;i<namac;i++){
			Camac&amac=*pamacList[i];
			float x=posList_amac[i].v[X];
			float z=posList_amac[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov_molecule)/2){
				amac.movloc_inFather(width_mov_molecule,0,0);//乘以0.5是为了缩小分布范围
				moved=true;
			}
			if(z<pos[Z]-(height_mov_molecule)/2){
				amac.movloc_inFather(0,0,height_mov_molecule);
				moved=true;
			}
			if(x>pos[X]+(width_mov_molecule)/2){
				amac.movloc_inFather(-width_mov_molecule,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov_molecule)/2){
				amac.movloc_inFather(0,0,-height_mov_molecule);
				moved=true;
			}
			if(moved){
				float amacnewpos[4];
				amac.getPosInFather(amacnewpos);
				//着陆
				float groundHorizon=ground.getH(amacnewpos[X],amacnewpos[Z]);
				if(groundHorizon>water.Horizon){
					amac.downToGround(20);
				}else{
					amac.downToWaterSurface();
					
				}
			}
			
		}
	}
		//将出界的can移到界内
	{
		int ncan=(int)pcanList.size();
		for(int i=0;i<ncan;i++){
			Ccan&can=*pcanList[i];
			float x=posList_can[i].v[X];
			float z=posList_can[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov)/2){
				can.movloc_inFather(width_mov,0,0);//乘以0.5是为了缩小分布范围
				moved=true;
			}
			if(z<pos[Z]-(height_mov)/2){
				can.movloc_inFather(0,0,height_mov);
				moved=true;
			}
			if(x>pos[X]+(width_mov)/2){
				can.movloc_inFather(-width_mov,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov)/2){
				can.movloc_inFather(0,0,-height_mov);
				moved=true;
			}
			if(moved){
				can.can.indexOfTextureID=18;
				can.dish.indexOfTextureID=19;
				float cannewpos[4];
				can.getPosInFather(cannewpos);
				//着陆
				float groundHorizon=ground.getH(cannewpos[X],cannewpos[Z]);
				if(groundHorizon>water.Horizon){
					can.downToGround(40,true);
				}else{
					can.downToWaterSurface();
					
				}
				can.life=can.lifemax;
			}
			
			
		}
	}
	//amac移动
	{
		int namac=(int)pamacList.size();
		for(int i=0;i<namac;i++){
			Camac&amac=*pamacList[i];
			if(amac.visible==false)continue;
			if(amac.isOnWater()){
				amac.floatOnWater();
				amac.rotloc010(20/2);
				//判断与house的碰撞
				float amacpos[4];
				amac.getPosInFather(amacpos);
				float e_back[4];
				float d=house.collisionTest_singlePoint(amacpos,amac.Rc,e_back);
				if(d>0){//与墙壁发生碰撞
					//移动
					float back[4];
					mul(d,e_back,back);
					amac.movloc_inFather(back[X],back[Y],back[Z]);
					//改变速度
					float *v=amac.v;//入射速度
					//反射速度v2=v-2*dot(v,e_back)*e_back
					//（下面令k=-2*dot(v,e_back)，u=k*e_back，则v2=v+u）
					float v2[4];
					float k=-2*dot(v,e_back);
					float u[4];
					mul(k,e_back,u);
					add(v,u,v2);//得到v2
					//用v2改写v
					veccopy(v2,v);
				}
			}	
			
		}
	}
	
	//将出界的ene移到界内
	{
		int nene=(int)peneList.size();
		for(int i=0;i<nene;i++){
			Cene&ene=*peneList[i];
			float x=posList_ene[i].v[X];
			float z=posList_ene[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov_molecule)/2){
				ene.movloc_inFather(width_mov_molecule,0,0);
				moved=true;
			}
			if(z<pos[Z]-(height_mov_molecule)/2){
				ene.movloc_inFather(0,0,height_mov_molecule);
				moved=true;
			}
			if(x>pos[X]+(width_mov_molecule)/2){
				ene.movloc_inFather(-width_mov_molecule,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov_molecule)/2){
				ene.movloc_inFather(0,0,-height_mov_molecule);
				moved=true;
			}
			if(moved){
				float enenewpos[4];
				ene.getPosInFather(enenewpos);
				//着陆
				float groundHorizon=ground.getH(enenewpos[X],enenewpos[Z]);
				if(groundHorizon>water.Horizon){
					ene.downToGround(20);
				}else{
					ene.downToWaterSurface();		
				}
			}
			
		}
	}
	//ene移动
	{
		int nene=(int)peneList.size();
		for(int i=0;i<nene;i++){
			Cene&ene=*peneList[i];
			if(ene.visible==false)continue;
			if(ene.isOnWater()){
				ene.floatOnWater();
				ene.rotloc010(40/2);
				//判断与house的碰撞
				float enepos[4];
				ene.getPosInFather(enepos);
				float e_back[4];
				float d=house.collisionTest_singlePoint(enepos,ene.Rc,e_back);
				if(d>0){//与墙壁发生碰撞
					//移动
					float back[4];
					mul(d,e_back,back);
					ene.movloc_inFather(back[X],back[Y],back[Z]);
					//改变速度
					float *v=ene.v;//入射速度
					//反射速度v2=v-2*dot(v,e_back)*e_back
					//（下面令k=-2*dot(v,e_back)，u=k*e_back，则v2=v+u）
					float v2[4];
					float k=-2*dot(v,e_back);
					float u[4];
					mul(k,e_back,u);
					add(v,u,v2);//得到v2
					//用v2改写v
					veccopy(v2,v);
				}
			}
		}
	}
	
	//将出界的gene移到界内
	{
		int ngene=(int)pgeneList.size();
		for(int i=0;i<ngene;i++){
			Cgene&gene=*pgeneList[i];
			float x=posList_gene[i].v[X];
			float z=posList_gene[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov_molecule)/2){
				gene.movloc_inFather(width_mov_molecule,0,0);
				moved=true;
			}
			if(z<pos[Z]-(height_mov_molecule)/2){
				gene.movloc_inFather(0,0,height_mov_molecule);
				moved=true;
			}
			if(x>pos[X]+(width_mov_molecule)/2){
				gene.movloc_inFather(-width_mov_molecule,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov_molecule)/2){
				gene.movloc_inFather(0,0,-height_mov_molecule);
				moved=true;
			}
			if(moved){
				float genenewpos[4];
				gene.getPosInFather(genenewpos);
				//着陆
				float groundHorizon=ground.getH(genenewpos[X],genenewpos[Z]);
				if(groundHorizon>water.Horizon){
					gene.downToGround(20);
				}else{
					gene.downToWaterSurface();
					
				}
			}
			
		}
	}
	//gene移动
	{
		int ngene=(int)pgeneList.size();
		for(int i=0;i<ngene;i++){
			Cgene&gene=*pgeneList[i];
			if(gene.visible==false)continue;
			if(gene.isOnWater()){
				gene.floatOnWater();
				//判断与house的碰撞
				float genepos[4];
				gene.getPosInFather(genepos);
				float e_back[4];
				float d=house.collisionTest_singlePoint(genepos,gene.Rc,e_back);
				if(d>0){//与墙壁发生碰撞
					//移动
					float back[4];
					mul(d,e_back,back);
					gene.movloc_inFather(back[X],back[Y],back[Z]);
					//改变速度
					float *v=gene.v;//入射速度
					//反射速度v2=v-2*dot(v,e_back)*e_back
					//（下面令k=-2*dot(v,e_back)，u=k*e_back，则v2=v+u）
					float v2[4];
					float k=-2*dot(v,e_back);
					float u[4];
					mul(k,e_back,u);
					add(v,u,v2);//得到v2
					//用v2改写v
					veccopy(v2,v);
				}
			}
		}
	}
	
	//将出界的autoCell移到界内
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			float x=posList_autoCell[i].v[X];
			float z=posList_autoCell[i].v[Z];
			bool moved=false;
			if(x<pos[X]-(width_mov)/2){
				autoCell.movloc_inFather(width_mov,0,0);
				moved=true;
			}
			if(z<pos[Z]-(height_mov)/2){
				autoCell.movloc_inFather(0,0,height_mov);
				moved=true;
			}
			if(x>pos[X]+(width_mov)/2){
				autoCell.movloc_inFather(-width_mov,0,0);
				moved=true;
			}
			if(z>pos[Z]+(height_mov)/2){
				autoCell.movloc_inFather(0,0,-height_mov);
				moved=true;
			}
		}
	}
	
	//将出界的arch移到界内
	{
		int narch=(int)parchList.size();
		for(int i=0;i<narch;i++){
			Carch&arch=*parchList[i];
			float x=arch.x;
			float z=arch.z;
			bool needreform=false;
			if(x<pos[X]-(width_mov)/2){
				arch.movloc_inFather(width_mov,0,0);
				arch.storexz(arch.x+width_mov,arch.z);
				needreform=true;
			}
			if(z<pos[Z]-(height_mov)/2){
				arch.movloc_inFather(0,0,height_mov);
				arch.storexz(arch.x,arch.z+height_mov);
				needreform=true;
			}
			if(x>pos[X]+(width_mov)/2){
				arch.movloc_inFather(-width_mov,0,0);
				arch.storexz(arch.x-width_mov,arch.z);
				needreform=true;
			}
			if(z>pos[Z]+(height_mov)/2){
				arch.movloc_inFather(0,0,-height_mov);
				arch.storexz(arch.x,arch.z-height_mov);
				needreform=true;
			}
			//重建arch
			if(needreform){
				//恢复生命
				arch.life=arch.lifemax;
				//
				Cstick&stick0=*arch.pstickList[0];
				Cstick&stick1=*arch.pstickList[1];
				Cstick&stick2=*arch.pstickList[2];
				Cstick&stick3=*arch.pstickList[3];
				Cstick&stick4=*arch.pstickList[4];
				Cstick&stick5=*arch.pstickList[5];
				//复位
				makeE(stick0.RMmat);
				makeE(stick1.RMmat);
				makeE(stick2.RMmat);
				makeE(stick3.RMmat);
				makeE(stick4.RMmat);
				makeE(stick5.RMmat);
				//设为冻结
				arch.setfreeze(true);
				//局部定位
				stick0.setPosInFather(100,0,0);
				stick1.setPosInFather(-100,0,0);
				stick3.setPosInFather(0,0,100);
				stick4.setPosInFather(0,0,-100);
				//全局定位
				float x=arch.x;
				float z=arch.z;
				//移到目标位置
				stick0.movloc(x,0,z);
				stick1.movloc(x,0,z);
				stick3.movloc(x,0,z);
				stick4.movloc(x,0,z);
				//调整高度
				stick0.downToGround(stick0.len()/2,true);
				stick1.downToGround(stick1.len()/2,true);
				stick3.downToGround(stick3.len()/2,true);
				stick4.downToGround(stick4.len()/2,true);
				//调整位姿
				//stick2的位姿
				{
					float head0[4];
					stick0.toFather(0,stick0.len()/2+stick0.d/2,0,1,head0);
					float head1[4];
					stick1.toFather(0,stick1.len()/2+stick1.d/2,0,1,head1);
					float half[4];
					add(head0,head1,half);
					mul(0.5,half,half);
					stick2.setPosInFather(half[X],half[Y],half[Z]);
					float vec[4];
					sub(head0,head1,vec);
					normalize(vec);
					stick2.setPosture_inFather(vec);
				}
				//stick5的位姿
				{
					float head3[4];
					stick3.toFather(0,stick3.len()/2+stick3.d/2,0,1,head3);
					float head4[4];
					stick4.toFather(0,stick4.len()/2+stick4.d/2,0,1,head4);
					float half[4];
					add(head3,head4,half);
					mul(0.5,half,half);
					stick5.setPosInFather(half[X],half[Y],half[Z]);
					float vec[4];
					sub(head4,head3,vec);
					normalize(vec);
					stick5.setPosture_inFather(vec);
				}	
			}
			if(showShadow){
				arch.mesh2mesh_world();
				arch.remakeBondEdgeList(light_pos);
				arch.remakeSV(light_pos);
			}
			
		}
	}
	//autoCell着陆
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			float x=posList_autoCell[i].v[X];
			float z=posList_autoCell[i].v[Z];
			//着陆
			float groundHorizon=ground.getH(x,z);
		
			if(groundHorizon>water.Horizon){
				autoCell.downToGround_soft(0.5/3,20);
			}else{
				autoCell.downToWaterSurface_soft(0.5/3);
			}
		
			
		}
	}

	


	//autoCell转动
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			if(autoCell.visible==false)continue;
			//进行转动
			if(!autoCell.isOnWater()){//在陆上
				autoCell.smartRot(*pcell,false);
			}else{//在水上
				autoCell.smartRot(*pcell,true);
			}
		}
	}
	//autoCell前进
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			//前进
			if(!autoCell.isOnWater()){//在陆上
				autoCell.advance(*pcell,false);
			}else{//在水上
				autoCell.advance(*pcell,true);
			}
			if(autoCell.visible==false)continue;//如果不可见，只前进即可，不做碰撞检测
			float *autoPos=posList_autoCell[i].v;//对于不要求很精确的检测，直接用autoCell的老位置即可
			//用新位置与house进行碰撞检测
			float e_back[4];//反弹方向
			float d=house.collisionTest_singlePoint(autoPos,autoCell.Rc,e_back);//打入深度
			if(d>0){//与house发生碰撞
				//反弹
				float back[4];//反弹向量
				mul(d,e_back,back);
				autoCell.movloc_inFather(back[X],back[Y],back[Z]);
				//将autoCell的前进方向调为与墙面平行
				//求autoCell的当前朝向向量
				float curdir[4];//当前朝向向量
				autoCell.toFather(0,0,-1,0,curdir);
				//对autoCell调整位姿
				//求与墙面平行的向量，即autoCell的目标朝向向量
				float tgdir[4];//目标朝向向量，tgdir=(back x curdir) x back
				float updn[4];
				cross(back,curdir,updn);
				cross(updn,back,tgdir);
				tgdir[Y]=0;//不能斜
				if(normalize(tgdir)==0){//如果得0向量
					//说明curdir与tgdir共线，不用调整
				}else{//得到tgdir
					//将朝向置为tgdir
					autoCell.setPostureWidthWantedDir_inFather(tgdir);
				}
			}
			
		}
	}
	//对每个autoCell计时
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			pautoCellList[i]->countTime();
		}
	}
	//每个autoCell蠕动
	{
		int nautoCell=(int)pautoCellList.size();
		for(int i=0;i<nautoCell;i++){
			if(pautoCellList[i]->visible)pautoCellList[i]->wri();
		}
	}
	//--------------------时钟-------------------------------------------------
	//arch的时钟
	{
		int narch=(int)parchList.size();
		for(int i=0;i<narch;i++){
			Carch&arch=*parchList[i];
			arch.timer_adjust_run();
		}
	}
	
	//---------------------景物运动---------------------------------------------
	//protein转动
	protein.rotloc100(10);
	protein.rotloc010(15);
	//天空盒跟随
	skyball.setPosInFather(pos[X],pos[Y],pos[Z]);
	//水面
	//将water.Horizon向着waterHorizon移动
	water.Horizon+=(waterHorizon-water.Horizon)*0.1;
	//水波浮动
	if(water.visible)water.wave();
	if(waterBox.visible)waterBox.wave(0.8,0.55);
	
	//实现water对主角的跟随为了保证水波和贴图的正确，需对二者进行平移
	float water_to_cell[4];
	sub(pos,pos_water,water_to_cell);
	//坐标平移向量
	float dx;
	float dz;
	dx=water_to_cell[X];
	dz=water_to_cell[Z];
	water.movRect(dx,dz);
	
	//-------------------主角----------------------------------------------------

	//起跳
	if(aKeyDown){
		if(!pcell->jump){//如果没跳起，才可以跳
			pcell->startJump(55);
		}
	}
	//获得house天花板高度
	float houseCeilH=house.getH_ceil(pos);
	//获得house地面，地面，水面三个高度
	float groundHorizon=ground.getH(pos[X],pos[Z]);
	float houseHorizon=house.getH_floor(pos);
	float waterHorizon=water.Horizon;
	//pcell中心应悬起的高度
	float H0=30;
	//*pcell自由落体
	if(pcell->jump){
		pcell->fall();
		//获得下落后坐标
		pcell->getPosInFather(pos);
		//判断是否接触天花板
		if(pos[Y]+H0>houseCeilH){
			pcell->vup=-20;//为了不与天花板发生“粘黏”，不是将vup设为0，而是设为一个负值（即给一个向下的初速度）
			pcell->setPosInFather(pos[X],houseCeilH-H0-10,pos[Z]);
			pos[Y]=houseCeilH-H0-10;//为了后面几个判断的正确，将pos[Y]同步更新
		}
		//判断是否接触地面
		else if(pos[Y]-H0<=groundHorizon){
			pcell->jump=false;
			//如果此处水面高，说明是落到水里了，则要播放落入水中的声音
			if(waterHorizon>groundHorizon){
				//播放声音
				alSource3f(source_fall_in_water, AL_POSITION, pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
				//根据fabs(vup)的大小决定音量
				float a,b;
				calLinearModel(15,0.05,87,1,a,b);
				float gain=a*fabs(pcell->vup)+b;
				gain=min(1,gain);//限制gain不超过1
				alSourcef(source_fall_in_water,AL_GAIN,gain);
				//播放
				alSourcePlay(source_fall_in_water);
			}

		}
		//判断是否接触house地面
		else if(pos[Y]-H0<=houseHorizon){
			pcell->jump=false;
			if(waterHorizon>houseHorizon){
				//播放声音
				alSource3f(source_fall_in_water, AL_POSITION, pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
				//根据fabs(vup)的大小决定音量
				float a,b;
				calLinearModel(15,0.05,87,1,a,b);
				float gain=a*fabs(pcell->vup)+b;
				gain=min(1,gain);//限制gain不超过1
				alSourcef(source_fall_in_water,AL_GAIN,gain);
				//播放
				alSourcePlay(source_fall_in_water);
			}
		}
		
	}
	
	int onWhich=0;//onWhich==0为在水面，onWhich==1为在地面，onWhich==2为在house地面
	
	//将*pcell的高度调整为max(house地面,地面,水面)
	if(pcell->jump==false){//非跳起时才落于地面
		//求pcell位置
		float pos[4];
		pcell->getPosInFather(pos);
		//求house地面，地面，水面三者高度的最大值并与pcell当前高度进行比较
		float Hmax=max(houseHorizon,max(groundHorizon,waterHorizon));
		if(pos[Y]>Hmax+H0+10){//如果停止下落时由于计算误差导致还没有着地，则进行一个轻微假跳
			//为了使当jumpable==false时也能跳起，绕过startJump直接手动设置，而不用pcell->startJump(5);
			pcell->vup=5;
			pcell->jump=true;
		}else{
			//判断主角当前位置是house地面高还是水面高还是地面高
			if(houseHorizon>groundHorizon&&houseHorizon>waterHorizon){//house地面最高
				pcell->setPosInFather(pos[X],houseHorizon+H0,pos[Z]);
				float norm[4]={0,1,0,1};
				pcell->setPosture_inFather_soft(norm);
				onWhich=2;
			}else{//不是house地面最高
				if(groundHorizon>waterHorizon){//地面最高
					if(pcell->bspeedup)pcell->downToGround_soft(0.65/3,20);
					else pcell->downToGround_soft(0.5/3,20);
					onWhich=1;
				}else{//水面最高
					pcell->downToWaterSurface_soft(0.5/3);
					onWhich=0;
					
				}
			}
		}
	}//得到onWhich
	
	
	
	//*pcell变色
	if(pcell->nomatch){
		int rd=timecounter%4;
		if(rd==0||rd==1){
			pcell->core.indexOfTextureID=2;
		}else if(rd==2||rd==3){
			pcell->core.indexOfTextureID=4;
		}
	}else{//不nomatch时一定要保证核是红的
		pcell->core.indexOfTextureID=2;
		
	}
	//*pcell各技能时钟更新
	pcell->timerscount();
	
	//*pcell蠕动
	pcell->wri();
	
	//发射炮弹
	if(dKeyDown){
		if(timecounter%3==0){
			pcell->fire();
			alSource3f(source_gun_small, AL_POSITION, pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
			alSourcePlay(source_gun_small);
		}
	}
	
	
	//炮弹运动
	pcell->cannonballsMov();
	//----------------------------------------------*pcell移动
	//移动前保存pcell的RTmat
	float RMmat[16];
	matcopy(pcell->RMmat,RMmat);
	//移动
	pcell->bmoving=false;
	if(upKeyDown){
		if(groundHorizon<water.Horizon&&pos[Y]-H0<=water.Horizon){
			pcell->movloc_pushWater(0,0,-pcell->getVlen());
		}else{
			pcell->movloc(0,0,-pcell->getVlen());
		}
		pcell->bmoving=true;
		
		
	}
	if(downKeyDown){
		if(groundHorizon<water.Horizon&&pos[Y]-H0<=water.Horizon){
			pcell->movloc_pushWater(0,0,pcell->getVlen());
		}else{
			pcell->movloc(0,0,pcell->getVlen());
		}
		pcell->bmoving=true;
		
	}
	//检测source_move_on_ground和source_move_on_water的播放状态
	ALint state_move_on_ground;
	ALint state_move_on_water;
	alGetSourcei(source_move_on_ground, AL_SOURCE_STATE,&state_move_on_ground);
	alGetSourcei(source_move_on_water, AL_SOURCE_STATE,&state_move_on_water);

	if(pcell->bmoving==true&&pcell->jump==false){//如果移动且未跳起
		if(onWhich==1||onWhich==2){//如果在地面或house地面
			if(state_move_on_water==AL_PLAYING){//停止source_move_on_water
				alSourceStop(source_move_on_water);
				//播放咕噜声
				alSource3f(source_water_gulu,AL_POSITION,pos[X]*k_soundDis,waterHorizon*k_soundDis,pos[Z]*k_soundDis);
				alSourcePlay(source_water_gulu);
			}
			if(state_move_on_ground!= AL_PLAYING){//如果source_move_on_ground已停止，则再次启动
				alSourcePlay(source_move_on_ground);
			}
			//更新声源位置
			alSource3f(source_move_on_ground,AL_POSITION,pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
		}else if(onWhich==0){//如果在水面
			if(state_move_on_ground==AL_PLAYING)alSourceStop(source_move_on_ground);//停止source_move_on_ground
			//检查source_move_on_water的状态
			if(state_move_on_water!= AL_PLAYING){//如果source_move_on_water已停止，则再次启动
				alSourcePlay(source_move_on_water);
			}
			//更新声源位置
			alSource3f(source_move_on_water,AL_POSITION,pos[X]*k_soundDis,pos[Y]*k_soundDis,pos[Z]*k_soundDis);
			

		
		}

	}else{//如果跳起
		if(state_move_on_ground==AL_PLAYING)alSourceStop(source_move_on_ground);//停止source_move_on_ground
		if(state_move_on_water==AL_PLAYING){//停止source_move_on_water
			alSourceStop(source_move_on_water);
			//播放咕噜声
			alSource3f(source_water_gulu,AL_POSITION,pos[X]*k_soundDis,waterHorizon*k_soundDis,pos[Z]*k_soundDis);
			alSourcePlay(source_water_gulu);
		}
		

	}
	//------------------------------*pcell移动后执行其与静态物体的碰撞检测，如果碰撞，则恢复
	//取得pcell移动后的新坐标
	pcell->getPosInFather(pos);
	//pcell与house的碰撞
	float e_back[4];
	float d=house.collisionTest_multiPoint_pcell(pos,pcell->Rc,e_back);
	if(d>0){
		//恢复
		matcopy(RMmat,pcell->RMmat);
		float back[4];
		mul(d*0.2,e_back,back);
		back[Y]=0;
		pcell->movloc_inFather(back[X],back[Y],back[Z]);
	}
	
	
	
	//*pcell与tree碰撞，使用网格机制
	{
		//获得碰撞列表
		float *pos1=pos;
		float R1=pcell->Rc;
		myvector<int> clist;
		treeCgrid.getclist(pos[X],pos[Z],clist);
		int nc=(int)clist.size();
		for(int i=0;i<nc;i++){
			int I=clist[i];//下标号
			Ctree&tree=*ptreeList[I];	
			if(tree.visible==false)continue;
			//检测tree与myCell的碰撞
			float *pos2=posList_tree[I].v;//tree位置
			float R2=tree.Rc;
			float dis2=pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z]);
			if(dis2<pow2(R1+R2)){//myCell与tree碰撞
				//回退
				float k=0.25;
				float backLen=((R1+R2)-CarmSqrt(dis2))*k;//碰撞的法向深度的k倍（软回退）
				float back[4];//回退向量
				sub((float(&)[4])(*pos1),(float(&)[4])(*pos2),back);
				if(normalize(back)==0)continue;
				mul(backLen,back,back);
				back[Y]=0;//舍弃Y分量
				//按back回退
				pcell->movloc_inFather(back[X],back[Y],back[Z]);
				break;
			}
			
		}
	}
	
	//pcell与protein的碰撞检测
	if(protein.visible){
		float R1=pcell->Rc;
		float R2=protein.Rc;
		float *pos1=pos;
		float pos2[4];//protein的坐标
		protein.getPosInFather(pos2);
		if(pow2(pos1[X]-pos2[X])+pow2(pos1[Y]-pos2[Y])+pow2(pos1[Z]-pos2[Z])<pow2(R1+R2)
			&&fabs(pos1[Y]-pos2[Y])<R2+R1/6){//碰撞
			//protein消失
			protein.visible=false;
			missionDone=true;
			//播放mission_done音效
			{
				alSource3f(source_mission_done,AL_POSITION,pos1[X]*k_soundDis,pos1[Y]*k_soundDis,pos1[Z]*k_soundDis);//用pos1而不用pos2
				alSourcePlay(source_mission_done);
			}
		}
	}
	//----------------------------------------------------*pcell旋转
	if(leftKeyDown){
		if(groundHorizon<water.Horizon&&pos[Y]-H0<=water.Horizon){
			pcell->rotloc_pushWater_010(7.0);
		}else{
			pcell->rotloc010(7.0);
		}
		pcell->bmoving=true;
	}
	if(rightKeyDown){
		if(groundHorizon<water.Horizon&&pos[Y]-H0<=water.Horizon){
			pcell->rotloc_pushWater_010(-7.0);
		}else{
			pcell->rotloc010(-7.0);
		}
		pcell->bmoving=true;
	}
	//-----------删除放在最后，为的是为了防止grid失效---------------------------------
	//-----------由于列表在循环中长度发生变化，所以若将上界提前固化，则循环体内应加n--
	//将life减为0的autoCell删除
	{
		int nautoCell=(int)pautoCellList.size();
		int count=0;
		for(int i=0;i<nautoCell;i++){
			CautoCell&autoCell=*pautoCellList[i];
			if(autoCell.life<=0){
				//主角获得分数
				pcell->score+=10;
				//从场景树上摘下来
				ground.ridchild(&autoCell);
				//加入到死亡敌菌列表
				pdiedautoCellList.push_back(&autoCell);
				count++;
			}else{
				if(count!=0)pautoCellList[i-count]=&autoCell;
			}
		}
		pautoCellList.resize(nautoCell-count);
	}
	//限制pdiedautoCellList的长度
	{
		const int maxLen=10;//pdiedautoCellList最大限制长度
		int ndiedautoCell=(int)pdiedautoCellList.size();
		if(ndiedautoCell>maxLen){
			//将pdiedautoCellList长度削减为maxLen_pautoCellList
			int ncut=ndiedautoCell-maxLen;
			for(int i=1;i<=ncut;i++){
				delete pdiedautoCellList[ndiedautoCell-i];
				pdiedautoCellList.pop_back();
			}
		}
	}
	//将标记为disapear的炮弹删除
	{
		int ncannonball=(int)pcell->pcannonballList.size();
		int count=0;
		for(int i=0;i<ncannonball;i++){
			Ccannonball&cannonball=*pcell->pcannonballList[i];
			if(cannonball.isdisapear()){
				ground.ridchild(&cannonball);//将炮弹从场景树上取下
				delete &cannonball;//删除炮弹对象
				count++;
			}else{
				if(count!=0)pcell->pcannonballList[i-count]=&cannonball;
			}
		}
		pcell->pcannonballList.resize(ncannonball-count);
	}
	//将标记为disapear的amac删除
	{
		int namac=(int)pamacList.size();
		int count=0;
		for(int i=0;i<namac;i++){
			Camac&amac=*pamacList[i];
			if(amac.isdisapear()){
				//从场景树上摘下来
				ground.ridchild(&amac);
				//删除
				delete pamacList[i];
				count++;
			}else{
				if(count!=0)pamacList[i-count]=&amac;
				
			}
		}
		pamacList.resize(namac-count);
	}
	//将标记为disapear的ene删除
	{
		int nene=(int)peneList.size();
		int count=0;
		for(int i=0;i<nene;i++){
			Cene&ene=*peneList[i];
			if(ene.isdisapear()){
				//从场景树上摘下来
				ground.ridchild(&ene);
				//删除
				delete peneList[i];
				count++;
			}else{
				if(count!=0)peneList[i-count]=&ene;
			}
		}
		peneList.resize(nene-count);
	}
	//将标记为disapear的gene删除
	{
		int ngene=(int)pgeneList.size();
		int count=0;
		for(int i=0;i<ngene;i++){
			Cgene&gene=*pgeneList[i];
			if(gene.isdisapear()){
				//从场景树上摘下来
				ground.ridchild(&gene);
				//删除
				delete pgeneList[i];
				count++;
			}else{
				if(count!=0)pgeneList[i-count]=&gene;
			}
		}
		pgeneList.resize(ngene-count);
	}
	
	//清除已结束的气泡
	{
		int nbubble=(int)pbubbleList.size();
		int count=0;
		for(int i=0;i<nbubble;i++){
			Cbubble&bubble=*pbubbleList[i];
			if(bubble.isdied){
				//从场景树上摘下来
				ground.ridchild(&bubble);
				//删除
				delete pbubbleList[i];
				count++;
			}else{
				if(count!=0)pbubbleList[i-count]=&bubble;
			}
		}
		pbubbleList.resize(nbubble-count);
	}
	//清除已结束的液滴
	{
		int ndrop=(int)pdropList.size();
		int count=0;
		for(int i=0;i<ndrop;i++){
			Cdrop&drop=*pdropList[i];
			if(drop.isdied){
				//从场景树上摘下来
				ground.ridchild(&drop);
				//删除
				delete pdropList[i];
				count++;
			}else{
				if(count!=0)pdropList[i-count]=&drop;
			}
		}
		pdropList.resize(ndrop-count);
	}
		//将已结束的atomburst加入pdiedatomburstList列表
	{
		int natomburst=(int)patomburstList.size();
		int count=0;
		for(int i=0;i<natomburst;i++){
			Catomburst&atomburst=*patomburstList[i];
			if(atomburst.isdied){
				//从场景树上摘下来
				ground.ridchild(&atomburst);
				//加入到pdiedatomburstList中
				pdiedatomburstList.push_back(&atomburst);
				count++;
			}else{
				if(count!=0)patomburstList[i-count]=&atomburst;
			}
		}
		patomburstList.resize(natomburst-count);
	}
	//限制pdiedatomburstList的长度
	{
		const int maxLen=6;//pdiedatomburstList最大限制长度
		int ndiedatomburst=(int)pdiedatomburstList.size();
		if(ndiedatomburst>maxLen){
			//将pdiedatomburstList长度削减为maxLen
			int ncut=ndiedatomburst-maxLen;
			for(int i=1;i<=ncut;i++){
				delete pdiedatomburstList[ndiedatomburst-i];
				pdiedatomburstList.pop_back();
			}
		}
	}
	//将visible==false的bigcannon加入pdiedbigcannonList列表
	{
		int nbigcannon=(int)pbigcannonList.size();
		int count=0;
		for(int i=0;i<nbigcannon;i++){
			Cbigcannon&bigcannon=*pbigcannonList[i];
			if(bigcannon.visible==false){
				//从场景树上摘下来
				ground.ridchild(&bigcannon);
				//加入到pdiedbigcannonList中
				pdiedbigcannonList.push_back(&bigcannon);
				count++;
			}else{
				if(count!=0)pbigcannonList[i-count]=&bigcannon;
			}
		}
		pbigcannonList.resize(nbigcannon-count);
	}
	//限制pdiedbigcannonList的长度
	{
		const int maxLen=15;//pdiedbigcannonList最大限制长度
		int ndiedbigcannon=(int)pdiedbigcannonList.size();
		if(ndiedbigcannon>maxLen){
			//将pdiedbigcannonList长度削减为maxLen
			int ncut=ndiedbigcannon-maxLen;
			for(int i=1;i<=ncut;i++){
				delete pdiedbigcannonList[ndiedbigcannon-i];
				pdiedbigcannonList.pop_back();
			}
		}
	}
	//将已结束的superburst删除
	{
		int nsuperburst=(int)psuperburstList.size();
		int count=0;
		for(int i=0;i<nsuperburst;i++){
			Csuperburst&superburst=*psuperburstList[i];
			if(superburst.isdied){
				//从场景树上摘下来
				ground.ridchild(&superburst);
				count++;
			}else{
				if(count!=0)psuperburstList[i-count]=&superburst;
			}
		}
		psuperburstList.resize(nsuperburst-count);
	}
	//将已结束的burst加入pdiedburstList列表
	{
		int nburst=(int)pburstList.size();
		int count=0;
		for(int i=0;i<nburst;i++){
			Cburst&burst=*pburstList[i];
			if(burst.isdied){
				//从场景树上摘下来
				ground.ridchild(&burst);
				//加入到pdiedburstList中
				pdiedburstList.push_back(&burst);
				count++;
			}else{
				if(count!=0)pburstList[i-count]=&burst;
			}
		}
		pburstList.resize(nburst-count);
	}
//	cout<<pdiedburstList.size()<<endl;
	//限制pdiedburstList的长度
	{
		const int maxLen=20;//pdiedburstList最大限制长度
		int ndiedburst=(int)pdiedburstList.size();
		if(ndiedburst>maxLen){
			//将pdiedburstList长度削减为maxLen_pburstList
			int ncut=ndiedburst-maxLen;
			for(int i=1;i<=ncut;i++){
				delete pdiedburstList[ndiedburst-i];
				pdiedburstList.pop_back();
			}
		}
	}
	//-------------增加放在最后，为了防止grid失效-----------------------------
	//增加气泡
	if((int)pbubbleList.size()<10){
		//随机生成坐标
		int x=pos[X]+(rand()%(int)areaWidth_god-areaWidth_god/2)*0.5;
		int z=pos[Z]+(rand()%(int)areaHeight_god-areaHeight_god/2)*0.5;
		//如果被地形覆盖，则不生成bubble，跳过
		float groundHorizon=ground.getH(x,z);
		if(groundHorizon<water.Horizon){//在水面，生成气泡
			//生成bubble
			Cbubble*pbubble=new Cbubble();
			pbubble->movloc(x,groundHorizon,z);
			pbubble->bubble.indexOfTextureID=9;
			ground.addchild(pbubble);
			pbubbleList.push_back(pbubble);
			//添加声音
			if(rand()%4==0){//让声音不那么密集
				pbubble->sourceMake(4);
				pbubble->sourceGain(0.2);
				pbubble->sourcePos(x,groundHorizon,z,k_soundDis);
				pbubble->sourcePlay();
			}

		}
	}
	//增加液滴
	if((int)pdropList.size()<5){
		//生成坐标
		int x=pos[X]+(rand()%(int)(areaWidth_god)-areaWidth_god/2)*0.6;
		int z=pos[Z]+(rand()%(int)(areaHeight_god)-areaHeight_god/2)*0.6;
		//判断是在地面还是在水面
		float groundHorizon=ground.getH(x,z);
		if(groundHorizon<water.Horizon){//在水面，生成液滴
			pdropList.grow();
			pdropList[(int)pdropList.size()-1]=new Cdrop();
			Cdrop&drop=*pdropList[(int)pdropList.size()-1];
			int colorIndex=rand()%(int)dropColorList.size();
			float R=dropColorList[colorIndex].R;
			float G=dropColorList[colorIndex].G;
			float B=dropColorList[colorIndex].B;
			drop.drop.setColour(R,G,B,1);
			drop.drop.indexOfTextureID=8;
			drop.movloc(x,waterHorizon,z);
			//加入到场景中
			ground.addchild(&drop);
			drop.setGround(&ground);
		}
		
	}
	//下面是一些补充较慢的东西，放在分频里进行
	switch(timecounter%20)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
		//增加新autoCell以维持autoCell数量为NautoCell
		if((int)pautoCellList.size()<NautoCell){
			//如果pdiedautoCellList中有元素，则从中拿出一个重新利用
			int ndiedautoCell=(int)pdiedautoCellList.size();
			if(ndiedautoCell!=0){//有元素，循环利用
				//从pdiedautoCellList中拿出一个元素
				//随机选取
				int I=rand()%ndiedautoCell;
				CautoCell*pautoCell=pdiedautoCellList[I];
				//将pautoCell重新初始化
				const int vlen=15/3;//死亡的细菌速度已发生了变化，所以速度需重新初始化
				int A=rand()*piDiv180;
				float vx=vlen*fastcos_LP(A);
				float vz=vlen*fastsin_LP(A);
				pautoCell->setV(vx,0,vz);
				int x=pos[X]+rand()%(int)(width_mov)-(width_mov)/2;
				int z=pos[Z]+rand()%(int)(height_mov)-(height_mov)/2;
				pautoCell->movloc(x,0,z);
				pautoCell->bflglr=false;//无鞭毛
				pautoCell->bshell=false;//无壳
				pautoCell->foot=false;//无脚（有脚的那个点，只是没有颜色）
				pautoCell->knee=false;//无膝（有膝的那个点，只是没有颜色）
				pautoCell->timecount=0;
				pautoCell->life=2;
				ground.addchild(pautoCell);
				//着陆
				float groundHorizon=ground.getH(x,z);
				if(groundHorizon>water.Horizon){
					pautoCell->downToGround(20);
				}else{
					pautoCell->downToWaterSurface();
					
				}
				//将pautoCell加入到pautoCellList
				pautoCellList.push_back(pautoCell);
				//用pdiedautoCellList中最后一个元素去补充位置I上的空缺
				//然后将pdiedautoCellList中最后一个元素删除
				if(ndiedautoCell==1){//如果原来pdiedautoCellList就只有一个元素，则不用补充空缺了
					//直接将最后一个元素删除
					pdiedautoCellList.pop_back();
				}else{//否则用最后一个元素补充I上的空缺，并删除最后一个元素
					pdiedautoCellList[I]=pdiedautoCellList[ndiedautoCell-1];
					pdiedautoCellList.pop_back();
				}
			}else{//pdiedautoCellList中没有元素，无法循环利用，只好再新建autoCell
				pautoCellList.grow();
				pautoCellList[(int)pautoCellList.size()-1]=new CautoCell();
				CautoCell&autoCell=*pautoCellList[(int)pautoCellList.size()-1];
				autoCell.indexOfTextureID=5;
				autoCell.core.indexOfTextureID=6;
				autoCell.movloc(0,40,0);
				const int vlen=15/3;
				int A=rand()*piDiv180;
				float vx=vlen*fastcos_LP(A);
				float vz=vlen*fastsin_LP(A);
				autoCell.setV(vx,0,vz);
				int x=pos[X]+rand()%(int)(width_mov)-(width_mov)/2;
				int z=pos[Z]+rand()%(int)(height_mov)-(height_mov)/2;
				autoCell.movloc(x,0,z);
				ground.addchild(&autoCell);
				autoCell.setGround(&ground);
				autoCell.setWater(&water);
				init4(autoCell.flglrcolor,70.0/255,1,70.0/255,1);
				autoCell.zoomloc0(0.45,0.45,0.45);
				autoCell.indexOfTextureID=3;
				autoCell.setRc(Rc_autoCell);
				//		autoCell.bshowBB=true;
				autoCell.core.indexOfTextureID=4;
				autoCell.bmoving=true;
				//着陆
				float groundHorizon=ground.getH(x,z);
				if(groundHorizon>water.Horizon){
					autoCell.downToGround(20);
				}else{
					autoCell.downToWaterSurface();
					
				}
			}
		}
		break;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		//生成新amac以维持数量为Namac
		if((int)pamacList.size()<Namac){
			pamacList.grow();
			pamacList[(int)pamacList.size()-1]=new Camac();
			Camac&amac=*pamacList[(int)pamacList.size()-1];
			int vlen=30/3;
			int A=rand()*piDiv180;
			float vx=vlen*fastcos_LP(A);
			float vz=vlen*fastsin_LP(A);
			amac.setV(vx,0,vz);
			int x=pos[X]+rand()%(int)(width_mov)-(width_mov)/2;
			int z=pos[Z]+rand()%(int)(height_mov)-(height_mov)/2;
			amac.movloc(x,0,z);
			amac.zoomloc(3,3,3);
			ground.addchild(&amac);
			amac.setGround(&ground);
			amac.setWater(&water);
			//   	amac.bshowBB=true;
			amac.setRc(Rc_amac);
			amac.rotloc010(rand());
			//着陆
			float groundHorizon=ground.getH(x,z);
			if(groundHorizon>water.Horizon){
				amac.downToGround(20);
			}else{
				amac.downToWaterSurface();
				
			}
			
		}
		break;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
		//生成新gene以维持数量为Ngene
		if((int)pgeneList.size()<Ngene){
			pgeneList.grow();
			pgeneList[(int)pgeneList.size()-1]=new Cgene();
			Cgene&gene=*pgeneList[(int)pgeneList.size()-1];
			int vlen=30/3;
			int A=rand()*piDiv180;
			float vx=vlen*fastcos_LP(A);
			float vz=vlen*fastsin_LP(A);
			gene.setV(vx,0,vz);
			int x=pos[X]+rand()%(int)areaWidth_god-areaWidth_god/2;
			int z=pos[Z]+rand()%(int)areaHeight_god-areaHeight_god/2;
			gene.movloc(x,0,z);
			gene.zoomloc(3,3,3);
			ground.addchild(&gene);
			gene.setGround(&ground);
			gene.setWater(&water);
			//		gene.bshowBB=true;
			gene.setRc(Rc_gene);
			//颜色
			int colorflg=rand()%7;
			switch(colorflg){
			case 0://生成全红基因
			case 1:
				{
					gene.effectID=1;
					for(int i=0;i<=5;i++)gene.ball[i].setColour(1,0,0,1);
				}
				break;
			case 2://生成全绿基因
				{
					gene.effectID=2;
					for(int i=0;i<=5;i++)gene.ball[i].setColour(0,1,0,1);
				}
				break;
			case 3://生成全蓝基因
			case 4:
				{
					gene.effectID=3;
					for(int i=0;i<=5;i++)gene.ball[i].setColour(0,0,1,1);
				}
				break;
			default://随机生成各球颜色，但必须保证六个球不同色
				{
					gene.effectID=0;
					//随机生成各球颜色
					for(int i=0;i<=5;i++){
						int index=rand()%3;
						switch(index){
						case 0:
							gene.ball[i].setColour(1,0,0,1);
							break;
						case 1:
							gene.ball[i].setColour(0,1,0,1);
							break;
						case 2:
							gene.ball[i].setColour(0,0,1,1);
							break;
						}
					}
					//再保证六个球不完全同色
					int index=rand()%5;//生成0,1,2,3,4中一个数
					//强制gene.ball[index]与gene.ball[5]不同色
					float r=gene.ball[5].colour[0];
					float g=gene.ball[5].colour[1];
					float b=gene.ball[5].colour[2];
					gene.ball[index].setColour(b,r,g,1);//这就保证了两者不同色
				}
				break;
			}
			
			//着陆
			float groundHorizon=ground.getH(x,z);
			if(groundHorizon>water.Horizon){
				gene.downToGround(20);
			}else{
				gene.downToWaterSurface();
				
			}
			
		}
		break;
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
		//生成新ene以维持数量为Nene
		if((int)peneList.size()<Nene){
			peneList.grow();
			peneList[(int)peneList.size()-1]=new Cene();
			Cene&ene=*peneList[(int)peneList.size()-1];
			int vlen=30/3;
			int A=rand()*piDiv180;
			float vx=vlen*fastcos_LP(A);
			float vz=vlen*fastsin_LP(A);
			ene.setV(vx,0,vz);
			int x=pos[X]+rand()%(int)(width_mov)-(width_mov)/2;
			int z=pos[Z]+rand()%(int)(height_mov)-(height_mov)/2;
			ene.movloc(x,0,z);
			ene.zoomloc(3,3,3);
			ground.addchild(&ene);
			ene.setGround(&ground);
			ene.setWater(&water);
			//	ene.bshowBB=true;
			ene.setRc(Rc_ene);
			ene.rotloc010(rand());
			//着陆
			float groundHorizon=ground.getH(x,z);
			if(groundHorizon>water.Horizon){
				ene.downToGround(20);
			}else{
				ene.downToWaterSurface();
				
			}
			
		}
		break;
	}
	//-------------------------------更新位置和方向
	//此步放在最后，是因为上面删除了一些对象，因此位置列表和朝向列表必须更新
	updatePosAndDir();
	//-----------------------------更新LOD等级或点线宽度
	//允许一定的迟缓，加一个分频
	//必须先updatePosAndDir，然后才能updateLODlevelAndPointOrLineSize
	//否则可能导致posList与对象列表不对应，尤其是当数量上也不对应，会引起崩溃
	updateLODlevelAndPointOrLineSize();
	//-------------------------------------------------------
	if(cheating){
		pcell->Ngun=4;
		pcell->ene[0].setColour(0,1,0,1);
		pcell->ene[1].setColour(0,1,0,1);
		pcell->ene[2].setColour(0,1,0,1);
		pcell->ene[3].setColour(0,1,0,1);
		pcell->setjumpable(true);
		pcell->speedup();
	}

}