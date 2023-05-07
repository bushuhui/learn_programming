int nx,ny;
nx = m_map->getSizeX();
ny = m_map->getSizeY();
for(int i=0;i<nx;i++)
{
    for(int j=0;j<ny;j++)
    {
        int32_t point=m_map->getMapItem(i,j);
        enum RMapItemType type;
        type=(enum RMapItemType) point;
        switch (type)
        {
            case RMAP_FREE:
                break;
            case RMAP_OBSTACLE:m_map->setMapItem(i,j,1);
                break;
            case RMAP_START_POINT:m_map->setMapItem(i,j,2);
                break;
            case RMAP_END_POINT:m_map->setMapItem(i,j,3);
                break;
            default:m_map->setMapItem(i,j,4);

        }

    }  
}

enum RMapItemType
    {
        RMAP_FREE = 0,					// 空白区域
        RMAP_OBSTACLE,					// 障碍物
        RMAP_OBSTACLE_UNDESCOVERED,		// 未被发现的障碍物
        RMAP_OBSTACLE_SCANNED,			// 已被扫描到的障碍物
        RMAP_START_POINT,				// 起点
        RMAP_END_POINT,					// 终点
        RMAP_CURRENT_POSITION,			// 当前点
        RMAP_OBSTACLE_EDGE				// 障碍物扩展的点
    };